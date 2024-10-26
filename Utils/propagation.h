#include "init-rna.h"
#include "sigmoide.h"


void feedforward(RNA *nn)
{
    // Calcul de la couche cachée
    for (int i = 0; i < nn->hidden_size; i++)
    {
        nn->hidden[i] = 0;
        for (int j = 0; j < nn->input_size; j++)
        {
            nn->hidden[i] += nn->input[j] * nn->w_input_hidden[i][j]; // Calculer la somme pondérée
        }
        nn->hidden[i] += nn->biais_hidden[i]; // Ajouter le biais de la couche cachée
        nn->hidden[i] = sigmoide_function(nn->hidden[i]); // Appliquer la fonction d'activation sigmoïde
    }

    // Calcul de la couche de sortie
    for (int i = 0; i < nn->output_size; i++) {
        nn->output[i] = 0;
        for (int j = 0; j < nn->hidden_size; j++) {
            nn->output[i] += nn->hidden[j] * nn->w_hidden_output[j][i]; 
        }
        nn->output[i] += nn->biais_output[i]; // Ajouter le biais de la couche de sortie
        nn->output[i] = sigmoide_function(nn->output[i]); // Appliquer la fonction d'activation
    }

}

