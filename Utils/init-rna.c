#include "matrix-functions.h"
// Structure du RNA 

typedef struct {
    int input_size; // nombre de neuronnes la couche d'entrée 
    int output_size; // nombre de neuronnes la couche de sortie 
    int hidden_size; // nombre de neuronnes de la couche cachée

    double *input; // un Pointeur vers le tableau des valeurs d'entrées ( des inputs )
    double *output; // un Pointeur vers le tableau des valeurs de sortie ( des outputs )
    double *hidden; // un Pointeur vers le tableau des valeurs de la couche cachée

    double **w_input_hidden; // Un poiteur vers le tableau des poids de la couche d'entrée à la couche cachée 
    double **w_hidden_output; // Un poiteur vers le tableau des poids de la chouche chachée vers la couche de sortie 

    double *biais_hidden; // vecteur des biais de la couche chachée
    double *biais_output; // vecteur des biais de la couche de sortie

}RNA;

void init_RNA(RNA *nn, int input_size, int output_size,int hidden_size )
{

    // Initialisation et allocation 
    nn->input_size=input_size;
    nn->output_size=output_size;
    nn->hidden_size=hidden_size;

    nn->input=(double *)malloc(nn->input_size * sizeof(double));
    nn->output=(double *)malloc(nn->output_size * sizeof(double));
    nn->hidden=(double *)malloc(nn->hidden_size * sizeof(double));

    nn->w_input_hidden=allocate_matrix(nn->input_size,nn->hidden_size);
    nn->w_hidden_output=allocate_matrix(nn->hidden_size,nn->output_size);

    nn->biais_hidden=(double *)malloc(nn->hidden_size*sizeof(double));
    nn->biais_output=(double *)malloc(nn->output_size*sizeof(double));




}