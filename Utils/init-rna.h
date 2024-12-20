#include "matrix-functions.h"
// Structure du RNA

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

void init_RNA(RNA *nn, int input_size, int output_size, int hidden_size)
{

    // Initialisation et allocation
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

    // Initialisation aléatoire des poids

    for (int i = 0; i < input_size; i++)
    {
        for (int j = 0; j < hidden_size; j++)
        {
            nn->w_input_hidden[i][j] = (rand() % 100) / 100.0;
        }
    }

    for (int i = 0; i < hidden_size; i++)
    {
        for (int j = 0; j < output_size; j++)
        {
            nn->w_hidden_output[i][j] = (rand() % 100) / 100.0;
        }
    }

    // Initialisation des biais

    for (int i = 0; i < hidden_size; i++)
    {
        nn->biais_hidden[i] = (rand() % 100) / 100.0;
    }
    for (int i = 0; i < output_size; i++)
    {
        nn->biais_output[i] = (rand() % 100) / 100.0;
    }
}

// Libération de la mémoire
void free_network(RNA *nn) {
    free(nn->input);
    free(nn->hidden);
    free(nn->output);
    free_matrix(nn->w_input_hidden, nn->input_size); // Libérer la mémoire des poids d'entrée à cachée
    free_matrix(nn->w_hidden_output, nn->hidden_size); // Libérer la mémoire des poids cachée à sortie
    free(nn->biais_hidden);
    free(nn->biais_output);
}