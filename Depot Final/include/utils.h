#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>

extern pthread_mutex_t mutex;

double sigmoide_function(double x);
double sigmoide_derivative(double x);
double **allocate_matrix(int rows, int cols);
void free_matrix(double **matrix, int rows);

#endif
