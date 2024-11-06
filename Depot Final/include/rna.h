#ifndef RNA_H
#define RNA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void init_RNA(RNA *nn, int input_size, int output_size, int hidden_size);
void free_network(RNA *nn);
void feedforward(RNA *nn);
void backpropagation(RNA *nn, double *target, double learning_rate);
void train(RNA *nn, double inputs[][2], double targets[], int num_samples, int epochs, double learning_rate);

#endif
