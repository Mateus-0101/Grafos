#include <stdio.h>
#include <stdlib.h>

struct no
{
    int valor;
    struct no* prox;
}no;

struct grafo
{
    int componentes;
    int qtd_vertices;
    int *visitado;
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

        printf("\nLista de adjacência do nó %d\n", i+1);

        while(aux != NULL)
        {
            printf("%d -> ", aux->valor);
            aux =aux->prox;
        }
    }
}

void DFS(struct grafo* g, int vertice)
{
    struct no* listaAdj = g->listaAdj[vertice];
    struct no* aux = listaAdj;

    g->visitado[vertice] = 1; //Nó inicial ou raiz
    printf("Visitado %d\n", vertice);

    if(g->listaAdj[vertice] == NULL)
    {
        return;
    }

    while(aux != NULL)
    {
        int vizinho = aux->valor; //Diz respetio ao vértice conectado a raiz atual

        if(g->visitado[vizinho] == 0)
        {
            //Visitará os vértices adjacentes ao vértice atual da pilha
            DFS(g, vizinho);
            g->componentes++;
        }

        aux = aux->prox;
    }
}

int main()
{
    int nos, arcos, u, v, cont;
    
    printf("Insira a quantidade de nos e arcos, respectivamente: ");
    scanf("%d %d", &nos, &arcos);
    
    struct grafo* g = criar_grafo(nos);
    
    for(int i = 0; i < arcos; i++)
    {
        printf("Insiras os nós conectados, u e v: ");
        scanf("%d %d", &u,&v);
        
        adicionar_arco(g,u,v);
    }
    
    struct no* aux = g->listaAdj;

    while(aux != NULL)
    {
        DFS(g, aux->valor);
        aux = aux->prox;
    }
    cont = g->componentes;
    cont--; //Retira primeira entrada
    
    printf("Componentes conectados: %d\n", cont);

    return 0;
}