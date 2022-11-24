#include <stdio.h>
#include <stdlib.h>

typedef struct aresta
{
    int vertice;
    int peso;
}aresta;

typedef struct elemento
{
    struct aresta ast;
    struct elemento *prox;
}elemento;

typedef struct lista
{
    int tamanho;
    struct elemento *inicio;
}lista;

typedef struct vertice
{
    int tamanho;
    int distancia;
    struct aresta list_adj[1000];
}vertice;

int vazio(lista *l)
{
    if(l->tamanho == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void incluir_lista(lista *l, int valor, int dist)
{
    if(l == NULL)
    {
        return;
    }

    elemento *novo = (elemento*)calloc(1,sizeof(elemento));
    elemento *aux = NULL, *ant = NULL;
    novo->ast.vertice = valor;
    novo->ast.peso = dist;

    if(vazio(l))
    {
        l->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = l->inicio;

        while(aux != NULL && !inserido)
        {
            if(aux->ast.peso < novo->ast.peso)
            {
                ant = aux;
                aux = aux->prox;
            }
            else
            {
                if(ant == NULL)
                {
                    l->inicio = novo;
                }
                else
                {
                    ant->prox = novo;
                }

                novo->prox = aux;
                inserido = 1;
            }
        }
        if(!inserido)
        {
            ant->prox = novo;
            inserido = 1;
        }
    }

    l->tamanho++;
}

aresta retirar_lista(lista *l)
{
    aresta ret;
    elemento *aux;

    if(vazio(l))
    {
        ret.vertice = -1;
        ret.peso = -1;
    }
    else
    {
        aux = l->inicio;
        l->inicio = l->inicio->prox;

        ret.vertice = aux->ast.vertice;
        ret.peso = aux->ast.peso;
        l->tamanho--;

        return ret;
    }
}

void dijkstra(vertice *v, int raiz)
{
    lista *l = (lista*)calloc(1,sizeof(lista));
    aresta atual, prox;
    int custo, filho;

    v[raiz].distancia = 0;

    incluir_lista(l,raiz,v[raiz].distancia);

    while(!vazio(l))
    {
        atual = retirar_lista(l);
        for(int i = 0; i < v[atual.vertice].tamanho; i++)
        {
            filho = v[atual.vertice].list_adj[i].vertice;
            prox = v[atual.vertice].list_adj[i];
            custo = atual.peso + prox.peso;

            if(custo < v[filho].distancia)
            {
                v[filho].distancia = custo;

                incluir_lista(l,filho,custo);
            }
        }
    }
}

int main()
{
    int qtd_vert, qtd_art, u, v, x;
    int infinito = 99999;
    aresta ast;

    scanf("%d %d", &qtd_vert, &qtd_art);

    vertice *vert = (vertice*)calloc(qtd_vert+1,sizeof(vertice));

    for(int i = 0; i < qtd_art; i++)
    {
        scanf("%d %d %d", &u, &v, &x);

        ast.peso = x;

        ast.vertice = v;
        vert[u].list_adj[vert[u].tamanho] = ast;
        vert[u].distancia = infinito;
        vert[u].tamanho++;

        ast.vertice = u;
        vert[v].list_adj[vert[v].tamanho] = ast;
        vert[v].distancia = infinito;
        vert[v].tamanho++;
    }

    dijkstra(vert,6);

    for(int i = 1; i <= qtd_vert; i++)
    {
        printf("Distância entre raiz e vértice %d = %d\n",i,vert[i].distancia);
    }

    return 0;
}