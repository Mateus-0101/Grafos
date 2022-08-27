#include <stdio.h>
#include <stdlib.h>

struct no
{
    int valor;
    struct no* prox;
}no;

struct grafo
{
    int qtd_vertices;
    struct no** listaAdj;
}grafo;

struct no* criar_no(int valor)
{
    struct no* novo = malloc(sizeof(struct no));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

struct grafo* criar_grafo(int qtd_vertices)
{
    struct grafo* g = malloc(sizeof(struct grafo));
    g->qtd_vertices = qtd_vertices;

    g->listaAdj = malloc(qtd_vertices  * sizeof(struct no));

    for(int i = 0; i < qtd_vertices; i++)
    {
        g->listaAdj[i] = NULL;
    }

    return g;
}

void adicionar_arco(struct grafo* g, int origem, int destino)
{
    //Multidirecional
    //Liga origem ao destino
    struct no* novo = criar_no(destino);
    novo->prox = g->listaAdj[origem];
    g->listaAdj[origem] = novo;

    //Liga destino a origem
    novo = criar_no(origem);
    novo->prox = g->listaAdj[destino];
    g->listaAdj[destino] = novo;
}

void mostrar_grafo(struct grafo* g)
{
    for(int i = 0; i < g->qtd_vertices; i++)
    {
        struct no* aux  =g->listaAdj[i];

        printf("\nVétice %d:\n ", i+1);

        while(aux != NULL)
        {
            printf("%d -> ", aux->valor);
            aux = aux->prox;
        }
        printf("\n");
    }
}

int main()
{
    int pares, origem, destino, vertices;

    printf("Insira o número de pares: ");
    scanf("%d", &pares);

    vertices = pares*2;

    struct grafo* g = criar_grafo(vertices);

    for(int i = 0; i < pares; i++)
    {
    
        printf("Insira o par %d: ", i+1);
        scanf("%d %d", &origem, &destino);

        adicionar_arco(g, origem, destino);
    }

    mostrar_grafo(g);

    return 0;
}