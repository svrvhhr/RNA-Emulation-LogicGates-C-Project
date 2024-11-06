#include "../include/rna.h"      
#include "../include/utils.h"    
#include <string.h>              
#include <pthread.h>             

// Fonction pour entraîner le réseau de neurones pour une porte logique spécifique
void *train_logic_gate(void *args)
{
    RNA nn;                       
    int input_size = 2, hidden_size = 2, output_size = 1;  
    init_RNA(&nn, input_size, output_size, hidden_size);  

    double(*inputs)[2];            // Pointeur pour stocker les entrées de la porte logique
    double *targets;               // Pointeur pour stocker les sorties attendues de la porte logique
    int epochs = 30000;            // Nombre d'époques (itérations d'entraînement)
    double learning_rate = 0.005;  // Taux d'apprentissage pour ajuster les poids
    const char *gate_name;         // Nom de la porte logique à entraîner

    // Pour améliorer les résultats :
    // - Diminuer le taux d'apprentissage
    // - Augmenter le nombre d'époques

    pthread_mutex_lock(&mutex);    // Verrouille l'accès pour éviter les conflits entre threads

    // Vérifie quelle porte logique doit être entraînée, selon l'argument reçu
    if (strcmp((char *)args, "AND") == 0)
    {
        // Données d'entrée et cibles pour la porte logique AND
        static double inputs_AND[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        static double targets_AND[4] = {0, 0, 0, 1};
        inputs = inputs_AND;
        targets = targets_AND;
        gate_name = "AND";
    }
    else if (strcmp((char *)args, "OR") == 0)
    {
        // Données d'entrée et cibles pour la porte logique OR
        static double inputs_OR[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        static double targets_OR[4] = {0, 1, 1, 1};
        inputs = inputs_OR;
        targets = targets_OR;
        gate_name = "OR";
    }
    else
    {
        // Données d'entrée et cibles pour la porte logique XOR
        static double inputs_XOR[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        static double targets_XOR[4] = {0, 1, 1, 0};
        inputs = inputs_XOR;
        targets = targets_XOR;
        gate_name = "XOR";
    }
    pthread_mutex_unlock(&mutex);  // Déverrouille l'accès pour permettre à d'autres threads de continuer

    // Entraîne le réseau de neurones avec les données spécifiées
    train(&nn, inputs, targets, 4, epochs, learning_rate);

    pthread_mutex_lock(&mutex);    // Verrouille l'accès pour l'affichage des résultats
    printf("Résultats pour la porte %s:\n", gate_name);
    for (int i = 0; i < 4; i++)
    {
        // Donne les entrées au réseau et effectue la propagation avant pour obtenir la sortie
        nn.input[0] = inputs[i][0];
        nn.input[1] = inputs[i][1];
        feedforward(&nn);  // Calcul de la sortie en fonction des entrées
        // Affiche les résultats : les entrées, la sortie calculée et la sortie attendue
        printf("Entrées: %.1f, %.1f - Sortie: %.4f - Attendue: %.1f\n", nn.input[0], nn.input[1], nn.output[0], targets[i]);
    }
    pthread_mutex_unlock(&mutex);  // Déverrouille l'accès après affichage des résultats

    free_network(&nn);             
    pthread_exit(NULL);            
}
