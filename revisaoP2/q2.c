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
    int distancia;
    int tamanho;
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

    if(vazio(f))
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
    fila *f = (fila*)calloc(1,sizeof(fila));
    int filho, atual;

    inserir_fila(f,raiz);

    v[raiz].distancia = 0;

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

                v[filho].visitado = 1;//Não conta ciclos

                inserir_fila(f,filho);
            }
        }
    }
}

int main()
{
    int qtd_vertices, qtd_aresta, qtd_teste, u, v;
    
    scanf("%d",&qtd_teste);

    int *resposta = (int*)calloc(qtd_teste+1,sizeof(int));

    for(int t = 0; t < qtd_teste; t++)
    {
        scanf("%d %d", &qtd_vertices, &qtd_aresta);

        vertice *vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

        for(int i = 0; i < qtd_aresta; i++)
        {
            scanf("%d %d", &u, &v);

            vertices[u].lista_adj[vertices[u].tamanho] = v;
            vertices[u].tamanho++;

            vertices[v].lista_adj[vertices[v].tamanho] = u;
            vertices[v].tamanho++;
        }

        BFS(vertices,1);

        resposta[t] = vertices[qtd_vertices].distancia;
        //printf("%d\n", vertices[qtd_vertices].distancia);
    }

    printf("\n");

    for(int i = 0; i < qtd_teste; i++)
    {
        printf("%d\n",resposta[i]);
    }
    
    return 0;
}