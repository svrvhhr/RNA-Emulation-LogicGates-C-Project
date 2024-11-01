#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rna.h"

int main()
{
    RNA nn;
    int input_size = 2;     
    int hidden_size = 2;    
    int output_size = 1;    

    srand(time(NULL));

    // Initialize the neural network
    init_RNA(&nn, input_size, output_size, hidden_size);

    // Training data for the AND gate
    double inputs[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
    double targets[4] = { 0, 0, 0, 1 }; // Expected outputs for AND

    // Train the network for the AND gate
    train(&nn, inputs, targets, 4, 20000, 0.01); 

    // Test the network after training
    for (int i = 0; i < 4; i++)
    {
        nn.input[0] = inputs[i][0];
        nn.input[1] = inputs[i][1];
        feedforward(&nn);
        printf("Input: (%.1f, %.1f) - Output: %.4f\n", nn.input[0], nn.input[1], nn.output[0]);
    }

    // Free allocated memory
    free_network(&nn);

    return 0;
}
