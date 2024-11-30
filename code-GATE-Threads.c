#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex;

double sigmoide_function(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoide_derivative(double x) {
    return x * (1.0 - x);
}

// Fonction pour allouer de la mémoire pour une matrice
double **allocate_matrix(int rows, int cols)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(cols * sizeof(double));
    }
    return matrix;
}

// Libération de la mémoire pour une matrice
void free_matrix(double **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

typedef struct
{
    int input_size;  // nombre de neuronnes la couche d'entrée
    int output_size; // nombre de neuronnes la couche de sortie
    int hidden_size; // nombre de neuronnes de la couche cachée

    double *input;  // un Pointeur vers le tableau des valeurs d'entrées ( des inputs )
    double *output; // un Pointeur vers le tableau des valeurs de sortie ( des outputs )
    double *hidden; // un Pointeur vers le tableau des valeurs de la couche cachée

    double **w_input_hidden;  // Un poiteur vers le tableau des poids de la couche d'entrée à la couche cachée
    double **w_hidden_output; // Un poiteur vers le tableau des poids de la chouche chachée vers la couche de sortie

    double *biais_hidden; // vecteur des biais de la couche chachée
    double *biais_output; // vecteur des biais de la couche de sortie

} RNA;

void init_RNA(RNA *nn, int input_size, int output_size, int hidden_size) {
    nn->input_size = input_size;
    nn->output_size = output_size;
    nn->hidden_size = hidden_size;
    nn->input = (double *)malloc(nn->input_size * sizeof(double));
    nn->output = (double *)malloc(nn->output_size * sizeof(double));
    nn->hidden = (double *)malloc(nn->hidden_size * sizeof(double));
    nn->w_input_hidden = allocate_matrix(nn->input_size, nn->hidden_size);
    nn->w_hidden_output = allocate_matrix(nn->hidden_size, nn->output_size);
    nn->biais_hidden = (double *)malloc(nn->hidden_size * sizeof(double));
    nn->biais_output = (double *)malloc(nn->output_size * sizeof(double));

    for (int i = 0; i < input_size; i++) {
        for (int j = 0; j < hidden_size; j++) {
            nn->w_input_hidden[i][j] = (rand() % 100) / 100.0;
        }
    }
    for (int i = 0; i < hidden_size; i++) {
        for (int j = 0; j < output_size; j++) {
            nn->w_hidden_output[i][j] = (rand() % 100) / 100.0;
        }
    }
    for (int i = 0; i < hidden_size; i++) {
        nn->biais_hidden[i] = (rand() % 100) / 100.0;
    }
    for (int i = 0; i < output_size; i++) {
        nn->biais_output[i] = (rand() % 100) / 100.0;
    }
}

void free_network(RNA *nn) {
    free(nn->input);
    free(nn->hidden);
    free(nn->output);
    free_matrix(nn->w_input_hidden, nn->input_size);
    free_matrix(nn->w_hidden_output, nn->hidden_size);
    free(nn->biais_hidden);
    free(nn->biais_output);
}

void feedforward(RNA *nn) {
    for (int i = 0; i < nn->hidden_size; i++) {
        nn->hidden[i] = 0;
        for (int j = 0; j < nn->input_size; j++) {
            nn->hidden[i] += nn->input[j] * nn->w_input_hidden[j][i];
        }
        nn->hidden[i] += nn->biais_hidden[i];
        nn->hidden[i] = sigmoide_function(nn->hidden[i]);
    }

    for (int i = 0; i < nn->output_size; i++) {
        nn->output[i] = 0;
        for (int j = 0; j < nn->hidden_size; j++) {
            nn->output[i] += nn->hidden[j] * nn->w_hidden_output[j][i];
        }
        nn->output[i] += nn->biais_output[i];
        nn->output[i] = sigmoide_function(nn->output[i]);
    }
}

void backpropagation(RNA *nn, double *target, double learning_rate) {
    double *output_errors = (double *)malloc(nn->output_size * sizeof(double));
    double *hidden_errors = (double *)malloc(nn->hidden_size * sizeof(double));

    for (int i = 0; i < nn->output_size; i++) {
        output_errors[i] = target[i] - nn->output[i];
    }

    for (int i = 0; i < nn->hidden_size; i++) {
        hidden_errors[i] = 0;
        for (int j = 0; j < nn->output_size; j++) {
            hidden_errors[i] += output_errors[j] * nn->w_hidden_output[i][j];
        }
        hidden_errors[i] *= sigmoide_derivative(nn->hidden[i]);
    }

    for (int i = 0; i < nn->output_size; i++) {
        for (int j = 0; j < nn->hidden_size; j++) {
            nn->w_hidden_output[j][i] += learning_rate * output_errors[i] * nn->hidden[j];
        }
    }

    for (int i = 0; i < nn->hidden_size; i++) {
        for (int j = 0; j < nn->input_size; j++) {
            nn->w_input_hidden[j][i] += learning_rate * hidden_errors[i] * nn->input[j];
        }
    }

    free(output_errors);
    free(hidden_errors);
}

void train(RNA *nn, double inputs[][2], double targets[], int num_samples, int epochs, double learning_rate) {
    for (int e = 0; e < epochs; e++) {
        for (int i = 0; i < num_samples; i++) {
            nn->input[0] = inputs[i][0];
            nn->input[1] = inputs[i][1];
            feedforward(nn);
            backpropagation(nn, &targets[i], learning_rate);
        }
    }
}

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

int main() {
    srand(time(NULL));
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threads[0], NULL, train_logic_gate, "AND");
    pthread_create(&threads[1], NULL, train_logic_gate, "OR");
    pthread_create(&threads[2], NULL, train_logic_gate, "XOR");

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
