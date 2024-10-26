#include "Utils/propagation.h"

int main()
{
    RNA nn ;
    init_RNA(&nn,2,1,2);

    // Définir les entrées pour la porte AND

    double test_AND[4][2]={{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    for (int i=0; i<4; i++)
    {
        nn.input[0]=test_AND[i][0];
        nn.input[1]=test_AND[i][1];

        feedforward(&nn);
        printf("Input: %d AND %d -> Output: %f\n", (int)nn.input[0], (int)nn.input[1], nn.output[0]);
    }
    free_network(&nn);
    return 0;
}
