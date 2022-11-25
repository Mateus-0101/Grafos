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
    struct aresta lista_adj[1000];
}vertice;

int vazio(fila *f)
{
    if(f->inicio == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void inserir_fila(fila *f, int v, int dist)
{
    if(f == NULL)
    {
        return;
    }
    //Insere ordenado -> menor no início
    elemento *novo = (elemento*)calloc(1,sizeof(elemento));
    elemento *aux = NULL, *ant = NULL;
    novo->ast.vertice = v;
    novo->ast.peso = dist;

    if(f->inicio == NULL)
    {
        f->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = f->inicio;

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
                    f->inicio = novo;
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

    f->tamanho++;
}

aresta retirar_fila(fila *f)
{
    aresta ret;
    elemento *aux;

    if(vazio(f))
    {
        ret.vertice = -1;
        ret.peso = -1;
    }
    else
    {
        aux = f->inicio;
        f->inicio = aux->prox;

        ret.vertice = aux->ast.vertice;
        ret.peso = aux->ast.peso;

        f->tamanho--;

        return ret;
    }
}
/*
void mostrar(vertice *v, int qtd_vertices)
{
    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVertices %d: ", i);

        for(int j = 0; j < v[i].tamanho; j++)
        {
            printf("-> %d ", v[i].lista_adj[j]);
        }
    }
}
*/

void dijkstra(vertice *v, int raiz)
{
    fila *f = (fila*)calloc(1,sizeof(fila));
    aresta atual;
    int filho, dist, custo; //custo = distancia atual + peso do proximo

    v[raiz].distancia = 0;

    inserir_fila(f,raiz,v[raiz].distancia);

    while(!vazio(f))
    {
        atual = retirar_fila(f);
        for(int i = 0; i < v[atual.vertice].tamanho; i++)
        {
            filho = v[atual.vertice].lista_adj[i].vertice;

            custo = atual.peso + v[atual.vertice].lista_adj[i].peso;

            if(custo < v[filho].distancia)
            {
                v[filho].distancia = custo;

                inserir_fila(f,filho,custo);
            }
        }
    }
}

int main()
{
    int qtd_vertices, qtd_arestas, raiz, u, v, x;
    int infinito = 99999;
    aresta ast;

    printf("Indique a quantidade de vértices e arestas na matriz:\n");
    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    printf("Indicação:\n1 = A\n2 = B\n3 = C\n4 = D\n...\n");
    printf("Escolha uma raíz para o Dijkstra:\n");
    scanf("%d", &raiz);
    printf("Inserir valores começando pela raiz\n");

    for(int i = 0 ; i < qtd_arestas; i++)
    {
        scanf("%d %d %d", &u, &v, &x);

        ast.peso = x;

        ast.vertice = v;
        vertices[u].lista_adj[vertices[u].tamanho] = ast;
        vertices[u].distancia = infinito;
        vertices[u].tamanho++;

        ast.vertice = x;
        vertices[v].lista_adj[vertices[v].tamanho] = ast;
        vertices[u].distancia = infinito;
        vertices[u].tamanho++;
    }

    dijkstra(vertices,raiz);

    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("Distância entre a %d e %d = %d\n", raiz, i, vertices[i].distancia);
    }
    

    return 0;
}