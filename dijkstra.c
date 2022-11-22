#include <stdio.h>
#include <stdlib.h>

typedef struct elemento
{
    int valor;
    struct elemento *prox;
}elemento;

typedef struct fila
{
    int tamanho;
    struct elemento *inicio;
    struct elemento *final;
}fila;

typedef struct vertice
{
    int visitado;
    int tamanho;
    int distancia;
    int peso;
    int lista_adj[1000];
}vertice;

int vazio(fila *f)
{
    if(f->tamanho == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void inserir_fila(fila *f, int x)
{
    elemento *novo = (elemento*)calloc(1,sizeof(elemento));
    novo->valor = x;

    if(f->tamanho == 0)
    {
        f->inicio = novo;
        f->final = novo;
    }
    else
    {
        f->final->prox = novo;
        f->final = novo;
    }
    f->tamanho++;
}

int retirar_fila(fila *f)
{
    if(vazio(f))
    {
        return -1;
    }
    else
    {
        int ret;

        ret = f->inicio->valor; //Retorno será o valor do primeiro da fila
        f->inicio = f->inicio->prox; //Novo início será o próximo da fila
        f->tamanho--;

        return ret;
    }
}

void BFS(vertice *v, int raiz)
{
    int atual, filho;
    fila *f = calloc(1,sizeof(fila));

    v[raiz].distancia = 0;
    

    inserir_fila(f,raiz);

    while(!vazio(f))
    {
        atual = retirar_fila(f);

        for(int i = 0; i < v[atual].tamanho; i++)
        {
            
        }
    }
}

void mostrar(vertice *v, int qtd_vertices)
{
    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVértice %d: ", i);

        for(int j = 0; j < v[i].tamanho; j++)
        {
            printf("-> ");
            printf("%d (%d) ",v[i].lista_adj[j], v[i].distancia);
        }
    }
}

int main()
{
    int qtd_vertices, qtd_arestas, raiz, u, v, x;
    int infinito = 99999;

    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0; i < qtd_arestas; i++)
    {
        scanf("%d %d %d", &u, &v, &x);

        vertices[u].lista_adj[vertices[u].tamanho] = v;
        vertices[u].tamanho++;
        vertices[u].peso = x;
        vertices[u].distancia = infinito;

        vertices[v].lista_adj[vertices[v].tamanho] = u;
        vertices[v].tamanho++;
        vertices[v].peso = x;
        vertices[v].distancia = infinito;
    }

    scanf("%d", &raiz);

    BFS(vertices, raiz); //Em BFS tem que indicar a raiz

    //mostrar(vertices,qtd_vertices);

    printf("\n");

    return 0;
}