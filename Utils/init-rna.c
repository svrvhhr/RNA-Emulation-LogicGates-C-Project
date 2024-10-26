#include <stdio.h>
#include <stdlib.h>

// Structure du RNA 

typedef struct RNA {
    int input_size; // nombre de neuronnes la couche d'entrée 
    int output_size; // nombre de neuronnes la couche de sortie 
    int hidden_size; // nombre de neuronnes de la couche cachée

    double *input; // un Pointeur vers le tableau des valeurs d'entrées ( des inputs )
    double *output; // un Pointeur vers le tableau des valeurs de sortie ( des outputs )
    double * hidden; // un Pointeur vers le tableau des valeurs de la couche cachée

    double* w_input_hidden; // Un poiteur vers le tableau des poids de la couche d'entrée à la couche cachée 
    double * w_hidden_output; // Un poiteur vers le tableau des poids de la chouche chachée vers la couche de sortie 

};

