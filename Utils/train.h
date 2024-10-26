#include "back-propa.h"
#include "propagation.h"


void train(RNA *nn, double **inputs, double **targets, int num_samples, int epochs, double learning_rate) {

// num_samples: Le nombre total d'échantillons dans votre ensemble d'entraînement.
// epochs : une itération complète sur l'ensemble des données d'entraînement. 
// Pendant une époque, le modèle reçoit toutes les données d'entraînement, effectue la propagation avant (feedforward) pour prédire les sorties, calcule l'erreur, puis effectue la rétropropagation (backpropagation) pour mettre à jour les poids du modèle.

    for (int e = 0; e < epochs; e++) {
        for (int i = 0; i < num_samples; i++) {
            // Copier les entrées dans le réseau avant de les perdre en appellant le feedforward
            for (int j = 0; j < nn->input_size; j++) {
                nn->input[j] = inputs[i][j];
            }
            
            // Phase de feedforward
            feedforward(nn);
            
            // Phase de rétropropagation : Ajuster les poids en fonction de l'erreur calculée par rapport aux cibles.
            backpropagation(nn, targets[i], learning_rate);
        }
    }
}
