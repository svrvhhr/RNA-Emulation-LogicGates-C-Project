#include "Utils/propagation.h"
#include "Utils/back-propa.h"
#include "Utils/test.h"
#include "Utils/train.h"




#include <stdio.h>
#include <stdlib.h>
#include "Utils/back-propa.h"
#include "Utils/test.h"
#include "Utils/train.h"

int main() {
    RNA nn;
    int input_size = 2;  // Nombre d'entrées
    int hidden_size = 2; // Nombre de neurones cachés
    int output_size = 1; // Nombre de sorties

    // Données d'entraînement pour les portes logiques
    double inputs[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
    
    // Cibles pour chaque porte logique (tableaux 2D)
    double and_targets[4][1] = { {0}, {0}, {0}, {1} }; // Porte AND
    double or_targets[4][1] = { {0}, {1}, {1}, {1} };  // Porte OR
    double xor_targets[4][1] = { {0}, {1}, {1}, {0} };  // Porte XOR

    // // Entraînement pour la porte AND
    // printf("Entraînement pour la porte AND:\n");
    // init_rna(&nn, input_size, hidden_size, output_size); // Initialisation du réseau
    // train(&nn, (double **)inputs, (double **)and_targets, 4, 10000, 0.1); // Entraînement
    // test(&nn, (double **)inputs, (double **)and_targets, 4); // Test
    // free_network(&nn); // Libération de la mémoire

    // // Entraînement pour la porte OR
    // printf("\nEntraînement pour la porte OR:\n");
    // init_rna(&nn, input_size, hidden_size, output_size); // Réinitialisation du réseau
    // train(&nn, (double **)inputs, (double **)or_targets, 4, 10000, 0.1); // Entraînement
    // test(&nn, (double **)inputs, (double **)or_targets, 4); // Test
    // free_network(&nn); // Libération de la mémoire

    // // Entraînement pour la porte XOR
    // printf("\nEntraînement pour la porte XOR:\n");
    // init_rna(&nn, input_size, hidden_size, output_size); // Réinitialisation du réseau
    // train(&nn, (double **)inputs, (double **)xor_targets, 4, 10000, 0.1); // Entraînement
    // test(&nn, (double **)inputs, (double **)xor_targets, 4); // Test
    // free_network(&nn); // Libération de la mémoire

    return 0;
}