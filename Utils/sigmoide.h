#include <math.h>

double segmoid(double x){
    return (1.0/(1.0+exp(-x)));
}

double sigmoide_derivative(double x){
    return (x*(1.0-x));
}

