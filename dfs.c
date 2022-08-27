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
    int *visitado;
    struct no** listaAdj;
}grafo;

void DFS(struct grafo* g, int vertice)
{
    struct no* listaAdj = g->listaAdj[vertice];
    struct no* aux = listaAdj;

    g->visitado[vertice] = 1; //Nó inicial
    printf("Visitado %d\n", vertice);

    while(aux != NULL)
    {
        int vizinho = aux->valor; //Diz respetio ao vértice conectado

        if(g->visitado[vizinho] == 0)
        {
            //Visitará os vértices adjacentes ao vértice atual da pilha -> Recursividade
            DFS(g, vizinho);
        }

        aux = aux->prox;
    }
}

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

    g->listaAdj = malloc(qtd_vertices * sizeof(struct no*));
    g->visitado = malloc(qtd_vertices * sizeof(int));

    for(int i = 0; i < qtd_vertices; i++)
    {
        g->listaAdj[i] = NULL;
        g->visitado[i] = 0;
    }

    return g;
}

void adicionar_arco(struct grafo* g, int origem, int destino)
{
    struct no* novo  = criar_no(destino);
    novo->prox = g->listaAdj[origem];
    g->listaAdj[origem] = novo;

    novo = criar_no(origem);
    novo->prox = g->listaAdj[destino];
    g->listaAdj[destino] = novo;
}

void mostrar_grafo(struct grafo* g)
{
    for(int i = 0; i < g->qtd_vertices; i++)
    {
        struct no* aux = g->listaAdj[i];

        printf("Lista de adjacência do nó %d\n", i);

        while(aux != NULL)
        {
            printf("%d -> ", aux->valor);
            aux =aux->prox;
        }
        printf("\n");
    }

}

int main()
{
    struct grafo* g = criar_grafo(4);

    adicionar_arco(g,2,5);
    adicionar_arco(g,3,6);
    adicionar_arco(g,1,2);
    adicionar_arco(g,1,4);

    mostrar_grafo(g);

    DFS(g,2);

    return 0;
}