/*
                ＴＲＡＢＡＬＨＯ ＰＲＯＧ ＩＩ
        Atílio Antônio Dadalto e Tiago da Cruz Santos
                       Data: 11/2018                         */

#include <stdio.h>
#include <stdlib.h>
// tirando pq não precisa mesmo, include nem dá erro
// #include <string.h>
// #include "include/ManipulaVetores.h"
// #include "include/Distancias.h"
#include "include/Classificador.h"
#include "include/ManipulaArquivos.h"

// vai ter que rolar uma modularização meu consacrated
/* além disso, meu parça, não quero ir na quinta pq não tem aula de eld,
   mas tinha que tirar umas duvidas do trabalho tipo sobre diretorios kkm */
int main()
{
    // Variáveis para o config.txt
    FILE *fconfig;
    FILE *ftreino;
    FILE *fteste;

    // Parâmetros do cálculo de distância (k vizinhos e r para Minkowski) e quantidade de parâmetros
    int *k, qtdP;
    float /* a[tam], b[tam], soma[tam], ordenadao[tam], distE, distM, distC, */ *r;
    // Endereço do treino e teste e parâmetros do cálculo de distância (de Euclides, Minkowski ou Chebyshev)
    char *pathTreino, *pathTeste, *pathEscrita, *d;

    float **treino;
    float **teste;
    int linhaTreino, colunaTreino, linhaTeste, colunaTeste;

    // Parâmetros de distância
    // se pa rola uma função pra malocar
    pathTreino = (char *)malloc(sizeof(char));
    pathTeste = (char *)malloc(sizeof(char));
    pathEscrita = (char *)malloc(sizeof(char));
    k = (int *)malloc(2 * sizeof(int));
    d = (char *)malloc(2 * sizeof(char));
    r = (float *)malloc(2 * sizeof(float));

    // Ex: abrindo config.txt (e printando resultados posteriormente)
    // Libera vetores e fecha programa caso não consiga abrir config
    fconfig = fopen("config.txt", "r");

    // se pa rola uma função pra fazer essa verificação (nem quero ver o tanto de parâmetro)
    if (fconfig == NULL)
    {
        printf("Nao foi possivel abrir o config.txt\n");
        free(k);
        free(r);
        free(d);
        free(pathTreino);
        free(pathTeste);
        free(pathEscrita);
        exit(1);
    }

    // Lê config desejada e abre treino e teste
    qtdP = leConfig(fconfig, &pathTreino, &pathTeste, &pathEscrita, &k, &d, &r);
    ftreino = fopen(pathTreino, "r");
    fteste = fopen(pathTeste, "r");

    if (ftreino == NULL)
    {
        printf("Nao foi possivel abrir o %s\n", pathTreino);

        free(k);
        free(r);
        free(d);
        free(pathTreino);
        free(pathTeste);
        free(pathEscrita);

        if (fteste != NULL)
        {
            fclose(fteste);
        }

        fclose(fconfig);

        exit(1);
    }

    if (fteste == NULL)
    {
        printf("Nao foi possivel abrir o %s\n", pathTeste);

        free(k);
        free(r);
        free(d);
        free(pathTreino);
        free(pathTeste);
        free(pathEscrita);

        if (ftreino != NULL)
        {
            fclose(ftreino);
        }

        fclose(fconfig);

        exit(1);
    }

    // Passa o conteúdo do treino e do teste para matriz
    treino = leDados(ftreino, &linhaTreino, &colunaTreino);
    teste = leDados(fteste, &linhaTeste, &colunaTeste);

    //? acho que isso pode ir módulo do classificador. talvez
    for (int i = 0; i < qtdP - 1; i++)
    {
        predict(i + 1, pathEscrita, k[i], d[i], r[i], treino, teste, colunaTreino + 1, linhaTreino - 1, colunaTeste + 1, linhaTeste - 1);
    }

    // free(all)
    // Libera vetores antes de fechar o programa
    free(k);
    free(r);
    free(d);
    free(pathTreino);
    free(pathTeste);
    free(pathEscrita);

    for (int j = 0; j < linhaTreino; j++)
    {
        free(treino[j]);
    }
    free(treino);

    for (int j = 0; j < linhaTeste; j++)
    {
        free(teste[j]);
    }
    free(teste);

    fclose(ftreino);
    fclose(fteste);
    fclose(fconfig);

    return 0;
}
