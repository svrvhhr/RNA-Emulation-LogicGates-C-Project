#include "train.h"

void test(RNA *nn, double **inputs, double *expected, int num_tests) {
    for (int i = 0; i < num_tests; i++) {
        // Copier les entrées dans le réseau
        for (int j = 0; j < nn->input_size; j++) {
            nn->input[j] = inputs[i][j];
        }
        
        // Phase de feedforward
        feedforward(nn);
        
        // Afficher les résultats
        printf("Output: %f, Expected: %f\n", nn->output[0], expected[i]);
    }
}
