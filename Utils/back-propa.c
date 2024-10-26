#include <stdlib.h>
#include "sigmoide.h"  
#include "init-rna.h"

void backpropagation(RNA *nn, double *target, double learning_rate) { // Target : Output desirés ; learning_rate : taux d'apprentissage -> voir readme
    double *output_errors = (double *)malloc(nn->output_size * sizeof(double));
    double *hidden_errors = (double *)malloc(nn->hidden_size * sizeof(double));

    // Calculer les erreurs de sortie
    for (int i = 0; i < nn->output_size; i++) {
        output_errors[i] = target[i] - nn->output[i];
    }

    // Calculer les erreurs de la couche cachée
    for (int i = 0; i < nn->hidden_size; i++) {
        hidden_errors[i] = 0;
        for (int j = 0; j < nn->output_size; j++) {
            hidden_errors[i] += output_errors[j] * nn->w_hidden_output[i][j];
        }
        hidden_errors[i] *= sigmoid_derivative(nn->hidden[i]);
    }

    // Mettre à jour les poids de la couche cachée vers la couche de sortie
    for (int i = 0; i < nn->output_size; i++) {
        for (int j = 0; j < nn->hidden_size; j++) {
            nn->w_hidden_output[j][i] += learning_rate * output_errors[i] * nn->hidden[j];
        }
    }

    // Mettre à jour les poids de la couche d'entrée vers la couche cachée
    for (int i = 0; i < nn->hidden_size; i++) {
        for (int j = 0; j < nn->input_size; j++) {
            nn->w_input_hidden[j][i] += learning_rate * hidden_errors[i] * nn->input[j];
        }
    }

    // Libérer la mémoire allouée
    free(output_errors);
    free(hidden_errors);
}
