#include "init-rna.h"
#include "sigmoide.h"


void feedforward(RNA *nn)
{
    // Calcul de la couche cachée
    for (int i = 0;i<nn->hidden_size;i++)
    {
        nn->hidden[i]=0;
        for (int j = 0;j<nn->input_size;j++)
        {
            nn->hidden[i]+= nn->input[j]*nn->w_input_hidden[i][j]; //appliquer la somme
        }
        nn->hidden[i]+= nn->biais_hidden[i]; // Ajouter le biais de la couche cachée
        nn->hidden[i]=sigmoide_function(nn->hidden[i]);
    }

}



