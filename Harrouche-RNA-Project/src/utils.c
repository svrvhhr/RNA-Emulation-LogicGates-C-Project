#include "../include/utils.h"
#include <stdlib.h>
#include <math.h>


double sigmoide_function(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoide_derivative(double x) {
    return x * (1.0 - x);
}

// Fonction pour allouer de la mémoire pour une matrice
double **allocate_matrix(int rows, int cols)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(cols * sizeof(double));
    }
    return matrix;
}

// Libération de la mémoire pour une matrice
void free_matrix(double **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

