#include "../include/rna.h"
#include "../include/utils.h"
#include <string.h>
#include <pthread.h>


void *train_logic_gate(void *args) {
    RNA nn;
    int input_size = 2, hidden_size = 2, output_size = 1;
    init_RNA(&nn, input_size, output_size, hidden_size);

    double (*inputs)[2];
    double *targets;
    int epochs = 20000;
    double learning_rate = 0.01;
    const char *gate_name;

    pthread_mutex_lock(&mutex);
    if (strcmp((char *)args, "AND") == 0) {
        static double inputs_AND[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
        static double targets_AND[4] = {0, 0, 0, 1};
        inputs = inputs_AND;
        targets = targets_AND;
        gate_name = "AND";
    } else if (strcmp((char *)args, "OR") == 0) {
        static double inputs_OR[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
        static double targets_OR[4] = {0, 1, 1, 1};
        inputs = inputs_OR;
        targets = targets_OR;
        gate_name = "OR";
    } else {
        static double inputs_XOR[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
        static double targets_XOR[4] = {0, 1, 1, 0};
        inputs = inputs_XOR;
        targets = targets_XOR;
        gate_name = "XOR";
    }
    pthread_mutex_unlock(&mutex);

    train(&nn, inputs, targets, 4, epochs, learning_rate);

    pthread_mutex_lock(&mutex);
    printf("Results for %s gate:\n", gate_name);
    for (int i = 0; i < 4; i++) {
        nn.input[0] = inputs[i][0];
        nn.input[1] = inputs[i][1];
        feedforward(&nn);
        printf("Inputs: %.1f, %.1f - Output: %.4f - Expected: %.1f\n", nn.input[0], nn.input[1], nn.output[0], targets[i]);
    }
    pthread_mutex_unlock(&mutex);

    free_network(&nn);
    pthread_exit(NULL);
}
