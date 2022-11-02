#include <stdio.h>
#include <stdlib.h>

void mostrar(int **m, int l, int c)
{
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < c; j++)
        {
            printf("\t%d",m[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int **matriz = (int**)malloc(sizeof(int*)*10);

    for(int i = 0; i < 10; i++)
    {
        matriz[i] = (int*)malloc(sizeof(int)*10);
    }

    mostrar(matriz,5,5);

    return 0;
}