#include "../include/rna.h"
#include "../include/utils.h"


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
void free_network(RNA *nn)
{
    free(nn->input);
    free(nn->hidden);
    free(nn->output);
    free_matrix(nn->w_input_hidden, nn->input_size);   // Libérer la mémoire des poids d'entrée à cachée
    free_matrix(nn->w_hidden_output, nn->hidden_size); // Libérer la mémoire des poids cachée à sortie
    free(nn->biais_hidden);
    free(nn->biais_output);
}

void feedforward(RNA *nn)
{
    // Calcul de la couche cachée
    for (int i = 0; i < nn->hidden_size; i++)
    {
        nn->hidden[i] = 0;
        for (int j = 0; j < nn->input_size; j++)
        {
            nn->hidden[i] += nn->input[j] * nn->w_input_hidden[j][i]; // Calculer la somme pondérée
        }
        nn->hidden[i] += nn->biais_hidden[i];             // Ajouter le biais de la couche cachée
        nn->hidden[i] = sigmoide_function(nn->hidden[i]); // Appliquer la fonction d'activation sigmoïde
    }

    // Calcul de la couche de sortie
    for (int i = 0; i < nn->output_size; i++)
    {
        nn->output[i] = 0;
        for (int j = 0; j < nn->hidden_size; j++)
        {
            nn->output[i] += nn->hidden[j] * nn->w_hidden_output[j][i];
        }
        nn->output[i] += nn->biais_output[i];             // Ajouter le biais de la couche de sortie
        nn->output[i] = sigmoide_function(nn->output[i]); // Appliquer la fonction d'activation
    }
}

void backpropagation(RNA *nn, double *target, double learning_rate)
{ // Target : Output desirés ; learning_rate : taux d'apprentissage -> voir readme
    double *output_errors = (double *)malloc(nn->output_size * sizeof(double));
    double *hidden_errors = (double *)malloc(nn->hidden_size * sizeof(double));

    // Calculer les erreurs de sortie
    for (int i = 0; i < nn->output_size; i++)
    {
        output_errors[i] = target[i] - nn->output[i];
    }

    // Calculer les erreurs de la couche cachée
    for (int i = 0; i < nn->hidden_size; i++)
    {
        hidden_errors[i] = 0;
        for (int j = 0; j < nn->output_size; j++)
        {
            hidden_errors[i] += output_errors[j] * nn->w_hidden_output[i][j];
        }
        hidden_errors[i] *= sigmoide_derivative(nn->hidden[i]);
    }

    // Mettre à jour les poids de la couche cachée vers la couche de sortie
    for (int i = 0; i < nn->output_size; i++)
    {
        for (int j = 0; j < nn->hidden_size; j++)
        {
            nn->w_hidden_output[j][i] += learning_rate * output_errors[i] * nn->hidden[j];
        }
    }

    // Mettre à jour les poids de la couche d'entrée vers la couche cachée
    for (int i = 0; i < nn->hidden_size; i++)
    {
        for (int j = 0; j < nn->input_size; j++)
        {
            nn->w_input_hidden[j][i] += learning_rate * hidden_errors[i] * nn->input[j];
        }
    }

    // Libérer la mémoire allouée
    free(output_errors);
    free(hidden_errors);
}
void train(RNA *nn, double inputs[][2], double targets[], int num_samples, int epochs, double learning_rate) {
    // num_samples: Le nombre total d'échantillons dans votre ensemble d'entraînement.
    // epochs : une itération complète sur l'ensemble des données d'entraînement.
    // Pendant une époque, le modèle reçoit toutes les données d'entraînement, effectue la propagation avant (feedforward) pour prédire les sorties, calcule l'erreur, puis effectue la rétropropagation (backpropagation) pour mettre à jour les poids du modèle.
 
    for (int e = 0; e < epochs; e++) {
        for (int i = 0; i < num_samples; i++) {
            // Copier les entrées dans le réseau
            nn->input[0] = inputs[i][0];
            nn->input[1] = inputs[i][1];

            // Phase de feedforward
            feedforward(nn);
            
            // Phase de rétropropagation
            backpropagation(nn, &targets[i], learning_rate); // Pass the address of the target
        }
    }
}