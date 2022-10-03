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

        ret = f->inicio->valor;
        f->inicio = f->inicio->prox;
        f->tamanho--;

        return ret;
    }
}

void BFS(vertice *v, int raiz)
{
    int atual, filho;
    fila *f = calloc(1,sizeof(fila));

    inserir_fila(f,raiz);

    while(!vazio(f))
    {
        atual = retirar_fila(f);
        v[atual].visitado = 1;

        for(int i = 0; i < v[atual].tamanho; i++)
        {
            filho = v[atual].lista_adj[i];

            if(v[filho].visitado == 0)
            {
                v[filho].distancia = v[atual].distancia + 1;

                inserir_fila(f,filho);
            }
        }
    }
}

int main()
{
    int qtd_vertices, qtd_arestas, raiz, u, v;

    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0; i < qtd_arestas; i++)
    {
        scanf("%d %d", &u, &v);

        vertices[u].lista_adj[vertices[u].tamanho] = v;
        vertices[u].tamanho++;
        vertices[v].lista_adj[vertices[v].tamanho] = u;
        vertices[v].tamanho++;
    }

    scanf("%d", &raiz);

    BFS(vertices, raiz); //Em BFS tem que indicar a raiz

    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nDistância entre vértice %d e raiz %d = %d\n", i,raiz,vertices[i].distancia);
    }

    return 0;
}