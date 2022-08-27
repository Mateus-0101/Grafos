#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct grafo
{
    int qtd_nos;
    bool **arcos;
} grafo;

void apagar_grafo(grafo* g)
{
    if(g->arcos == NULL)
    {
        return;
    }

    for(int i = 0; i < g->qtd_nos; i++)
    {
        if(g->arcos[i] != NULL)
        {
            free(g->arcos[i]); //Não perimete apagar arcos que NÃO foram alocados
        }
    }

    free(g->arcos);
    free(g);
};

grafo *criar_grafo(int qtd_nos)
{
    grafo *g = malloc(sizeof(*g));
    if(g == NULL)
    {
        return NULL; //verificar alocação de memória
    }

    g->qtd_nos = qtd_nos;

    //alocar matriz
    g->arcos = calloc(sizeof(bool*), g->qtd_nos); //alocando vetores de booleanos
    if(g->arcos == NULL)
    {
        free(g);
        return NULL; //liberar nós vazios
    }

    for(int i = 0; i < g->qtd_nos; i++)
    {
        g->arcos[i] = calloc(sizeof(bool), g->qtd_nos);
        if(g->arcos[i] == NULL)
        {
            //limpar de novo caso não seja possível alocar
            apagar_grafo(g);
            return NULL;
        }
    }

    return g; //Se chegar aqui, todas as alocações foram bem sucedidas
};


void imprimir_grafo(grafo *g)
{
    printf("digraph {\n");

    for(int origem = 0; origem < g->qtd_nos; origem++)
    {
        for(int destino = 0; destino < g->qtd_nos; destino++)
        {
            if(g->arcos[origem][destino]) //Indica o no de origem e destino do arco
            {
                printf("%d -> %d;\n", origem, destino);
            }
        }
    }

    printf("}\n");
};

bool arco_existe(grafo *g, unsigned int no_origem, unsigned int no_destino)
{
    return g->arcos[no_origem][no_destino];
};

bool inserir_arco(grafo *g, int no_origem, int no_destino)
{
    if(arco_existe(g, no_origem, no_destino))
    {
        return false;
    }

    g->arcos[no_origem][no_destino] = true;
    return true;
};


int main()
{
    grafo *g1 = criar_grafo(5);

    inserir_arco(g1,1,2);
    inserir_arco(g1,1,4);
    inserir_arco(g1,2,5);
    inserir_arco(g1,3,6);
    inserir_arco(g1,2,4);

    imprimir_grafo(g1);

    apagar_grafo(g1);

    return 0;
}