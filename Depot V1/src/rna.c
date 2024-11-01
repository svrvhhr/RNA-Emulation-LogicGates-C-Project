#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rna.h"

// Sigmoid activation function
double sigmoide_function(double x)
{
    return (1.0 / (1.0 + exp(-x)));
}

// Sigmoid derivative
double sigmoide_derivative(double x)
{
    return (x * (1.0 - x));
}

// Function to allocate memory for a matrix
double **allocate_matrix(int rows, int cols)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(cols * sizeof(double));
    }
    return matrix;
}

// Free memory for a matrix
void free_matrix(double **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Initialize the neural network
void init_RNA(RNA *nn, int input_size, int output_size, int hidden_size)
{
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

    // Random initialization of weights
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

    // Initialize biases
    for (int i = 0; i < hidden_size; i++)
    {
        nn->biais_hidden[i] = (rand() % 100) / 100.0;
    }
    for (int i = 0; i < output_size; i++)
    {
        nn->biais_output[i] = (rand() % 100) / 100.0;
    }
}

// Free allocated memory
void free_network(RNA *nn)
{
    free(nn->input);
    free(nn->hidden);
    free(nn->output);
    free_matrix(nn->w_input_hidden, nn->input_size);
    free_matrix(nn->w_hidden_output, nn->hidden_size);
    free(nn->biais_hidden);
    free(nn->biais_output);
}

// Feedforward process
void feedforward(RNA *nn)
{
    for (int i = 0; i < nn->hidden_size; i++)
    {
        nn->hidden[i] = 0;
        for (int j = 0; j < nn->input_size; j++)
        {
            nn->hidden[i] += nn->input[j] * nn->w_input_hidden[j][i];
        }
        nn->hidden[i] += nn->biais_hidden[i];
        nn->hidden[i] = sigmoide_function(nn->hidden[i]);
    }

    for (int i = 0; i < nn->output_size; i++)
    {
        nn->output[i] = 0;
        for (int j = 0; j < nn->hidden_size; j++)
        {
            nn->output[i] += nn->hidden[j] * nn->w_hidden_output[j][i];
        }
        nn->output[i] += nn->biais_output[i];
        nn->output[i] = sigmoide_function(nn->output[i]);
    }
}

// Backpropagation process
void backpropagation(RNA *nn, double *target, double learning_rate)
{
    double *output_errors = (double *)malloc(nn->output_size * sizeof(double));
    double *hidden_errors = (double *)malloc(nn->hidden_size * sizeof(double));

    // Calculate output errors
    for (int i = 0; i < nn->output_size; i++)
    {
        output_errors[i] = target[i] - nn->output[i];
    }

    // Calculate hidden errors
    for (int i = 0; i < nn->hidden_size; i++)
    {
        hidden_errors[i] = 0;
        for (int j = 0; j < nn->output_size; j++)
        {
            hidden_errors[i] += output_errors[j] * nn->w_hidden_output[i][j];
        }
        hidden_errors[i] *= sigmoide_derivative(nn->hidden[i]);
    }

    // Update weights from hidden to output
    for (int i = 0; i < nn->output_size; i++)
    {
        for (int j = 0; j < nn->hidden_size; j++)
        {
            nn->w_hidden_output[j][i] += learning_rate * output_errors[i] * nn->hidden[j];
        }
    }

    // Update weights from input to hidden
    for (int i = 0; i < nn->hidden_size; i++)
    {
        for (int j = 0; j < nn->input_size; j++)
        {
            nn->w_input_hidden[j][i] += learning_rate * hidden_errors[i] * nn->input[j];
        }
    }

    free(output_errors);
    free(hidden_errors);
}

// Train the neural network
void train(RNA *nn, double inputs[][2], double targets[], int num_samples, int epochs, double learning_rate)
{
    for (int e = 0; e < epochs; e++)
    {
        for (int i = 0; i < num_samples; i++)
        {
            nn->input[0] = inputs[i][0];
            nn->input[1] = inputs[i][1];
            feedforward(nn);
            backpropagation(nn, &targets[i], learning_rate);
        }
    }
}
