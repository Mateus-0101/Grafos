#include <stdio.h>
#include <stdlib.h>

struct vertice
{
    int destino;
    struct vertice* prox;
}vertice;

struct listaAdj
{
    struct vertice* inicio;
}listaAdj;

struct grafo //Grafo é um verto de listas adjacentes
{
    int qtd_vertices;
    struct listaAdj* vetor;
} grafo;

struct vertice *criar_vertice(int destino)
{
    struct vertice *novo = (struct vertice*)malloc(sizeof(struct vertice));

    novo->destino = destino;
    novo->prox = NULL;

    return novo;
}

struct grafo *criar_grafo(int qtd_vertices)
{
    struct grafo *g = (struct grafo*)malloc(sizeof(struct grafo));

    g->qtd_vertices = qtd_vertices;

    //Criar vetor de lista de adjacencia, de tamanho "qtd_vetices"
    g->vetor = (struct listaAdj*)malloc(qtd_vertices * sizeof(struct listaAdj));

    //Inicializar cada lista como vazia, fazendo o inicio como NULL
    for(int i = 0; i < qtd_vertices; i++)
    {
        g->vetor[i].inicio = NULL;
    }

    return g;
}


void inserir_arco(struct grafo* g, int origem, int destino)
{
    //Adiciona um arco da orgiem ao destino. Um vertice novo é adicionado
    //a lista de adjacencia da origem. O vertice é colocado no inicio.
    struct vertice *aux  = NULL;
    struct vertice *novo = criar_vertice(destino);

    if(g->vetor[origem].inicio == NULL)
    {
        novo->prox  = g->vetor[origem].inicio;
        g->vetor[origem].inicio = novo;
    }
    else
    {
        aux = g->vetor[origem].inicio;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novo;
    }

    //Grafo bidirecional, adicionar arco do destino a origem
    novo = criar_vertice(origem);

    if(g->vetor[destino].inicio == NULL)
    {
        novo->prox = g->vetor[destino].inicio;
        g->vetor[destino].inicio = novo;
    }
    else
    {
        aux = g->vetor[destino].inicio;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novo;
    }
}

void mostrar_grafo(struct grafo *g)
{
    for(int i = 0; i < g->qtd_vertices; i++)
    {
        struct vertice *indice = g->vetor[i].inicio;

        printf("\nLista de adjacência do vétice %d\n Inicio ", i+1);

        while(indice)
        {
            printf("-> %d", indice->destino);
            indice = indice->prox;
        }
        printf("\n");
    }
}
int main()
{
    int n;
    struct grafo* g = criar_grafo(5);

    printf("Insira o número de pares: ");
    scanf("%d", &n);


    inserir_arco(g,1,2);
    inserir_arco(g,1,4);
    inserir_arco(g,2,5);
    inserir_arco(g,3,6);
    inserir_arco(g,1,4);

    mostrar_grafo(g);

    return 0;
}