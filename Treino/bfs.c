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
    int list_adj[1000];
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

void inserir(fila *f, int valor)
{
    if(f == NULL)
    {
        return;
    }

    elemento *novo = (elemento*)calloc(1,sizeof(elemento));
    novo->valor = valor;

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

int retirar(fila *f)
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
    int atual,filho;

    v[raiz].distancia = 0;

    inserir(f,raiz);

    while(!vazio(f))
    {
        atual = retirar(f);
        v[atual].visitado = 1;
        for(int i = 0; i < v[atual].tamanho; i++)
        {
            filho = v[atual].list_adj[i];

            if(v[filho].visitado == 0)
            {
                v[filho].distancia = v[atual].distancia + 1;
                v[filho].visitado = 1;

                inserir(f,filho);
            }
        }
    }
}

int main()
{
    int qtd_vert, qtd_art, u, v;

    scanf("%d %d", &qtd_vert, &qtd_art);

    vertice *vert = (vertice*)calloc(qtd_vert+1,sizeof(vertice));

    for(int i = 0; i < qtd_art; i++)
    {
        scanf("%d %d", &u, &v);

        vert[u].list_adj[vert[u].tamanho] = v;
        vert[u].tamanho++;

        vert[v].list_adj[vert[v].tamanho] = u;
        vert[v].tamanho++;
    }

    BFS(vert,1);

    return 0;
}