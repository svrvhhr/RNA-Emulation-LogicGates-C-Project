#ifndef RNA_H
#define RNA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int input_size;
    int output_size;
    int hidden_size;
    double *input;
    double *output;
    double *hidden;
    double **w_input_hidden;
    double **w_hidden_output;
    double *biais_hidden;
    double *biais_output;
} RNA;

void init_RNA(RNA *nn, int input_size, int output_size, int hidden_size);
void free_network(RNA *nn);
void feedforward(RNA *nn);
void backpropagation(RNA *nn, double *target, double learning_rate);
void train(RNA *nn, double inputs[][2], double targets[], int num_samples, int epochs, double learning_rate);

#endif
