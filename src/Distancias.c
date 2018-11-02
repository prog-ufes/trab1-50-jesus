#include "../include/Distancias.h"
#include "../include/ManipulaVetores.h"
#include "../include/Classificador.h"
#include <stdio.h>
#include <math.h>

void distEuclid(float p[], float q[], int k, float *distE)
{
    float i, s[k], distancias = 0;

    subVet(p, q, k, s);                  // (pi - qi), ..., (pn - qn)
    quadradoVet(s, k, s);                // (pi - qi)^2, ..., (pn - qn)^2
    somaElementosVet(s, k, &distancias); // (pi - qi)^2 + ... + (pn - qn)^2

    *distE = sqrt(distancias);
    round2(distE);
}

void distMinkowski(float p[], float q[], int k, float r, float *distM)
{
    float i, s[k], distancias = 0;

    subVet(p, q, k, s);
    absVet(s, k, s);
    expVet(s, k, r, s);
    somaElementosVet(s, k, &distancias);
    distancias = pow(distancias, 1 / r);
    *distM = distancias;
}

// que merda é essa
void distChebyshev(float p[], float q[], int k, float *distC)
{
    float distE, s[k], distancias = 0;

    subVet(p, q, k, s);
    absVet(s, k, s);
    printaVet(s, k);
    *distC = maiorVet(s, k);
}

/*
int main()
{
    int i, k, stotal, distE;

    printf("k: ");
    scanf("%i", &k);

    int p[k], q[k], s[k];

    leVet(p, k);
    leVet(q, k);

    distEuclid(p, q, s, k, &distE);
    printf("Distancia euclidiana: %i", distE);

    return 0;
}
*/
