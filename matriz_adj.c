#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pares, p1 = 0, p2 = 0; //número de pares e os repectivos elementos
    int matriz_adj[99][99]; //Tamanho da matriz a ser utilizada


    printf("Insira o número de pares: ");
    scanf("%d", &pares);


    for(int i = 0; i < pares; i++)
    {
        printf("Insira o par %d: ", i+1);
        scanf("%d %d", &p1, &p2);
        matriz_adj[p1][p2] = 1; //liga o par indicado
        matriz_adj[p2][p1] = 1; //ligação multidirecional
        matriz_adj[p1][p1] = 1; //no sempre ligado com ele mesmo
        matriz_adj[p2][p2] = 1; //no sempre ligado com ele mesmo
    }

    printf("\n");
    
    //Mostrar matriz (apenas linhas com preenchimento)

    for(int i = 0; i < pares; i++)
    {
        if(matriz_adj [i][i] != 0) //detecta se a diagonal principal da linha foi utilizada
        {
            for(int j = 0; j < pares; j++) 
            {
                if(matriz_adj[j][j] != 0) //detecta se a diagonal principal da coluna foi utilizada
                {
                    printf("%d", matriz_adj[i][j]); //imprime elemento da matriz
                }
            }    
        }
        printf("\n");
    }

    return 0;
}