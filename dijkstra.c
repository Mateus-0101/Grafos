#include <stdio.h>
#include <stdlib.h>

typedef struct elemento
{
    int valor;
    int prioridade;
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

int topo(fila *f)
{
    return f->inicio->valor;
}

void inserir_fila(fila *f, int x)
{
    elemento *novo = (elemento*)calloc(1,sizeof(elemento));
    elemento *aux = (elemento*)calloc(1,sizeof(elemento));
    novo->valor = x;
    novo->prioridade = x;

    //Novo elementento possui maior prioridade que o inicio da lista
    if(f->inicio->prioridade < novo->prioridade)
    {
        novo->prox = f->inicio;
        f->inicio = novo;
    }
    else
    {
        //Percorre fila até achar posição adequada para o elemento
        while(aux->prox != NULL && aux->prox->prioridade > novo->prioridade)
        {
            aux = aux->prox;
        }

        //Reorganiza fila
        novo->prox = aux->prox;
        aux->prox = novo;
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
        elemento *aux = (elemento*)calloc(1,sizeof(elemento));
        aux = f->inicio;
        f->inicio = f->inicio->prox;

        return aux->valor;
        free(aux);
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

            if(v[atual].distancia + v[filho].distancia < v[filho].distancia)
            {
                v[atual].distancia = v[filho].distancia;

                inserir_fila(f,filho);
            }
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

    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0; i < qtd_arestas; i++)
    {
        scanf("%d %d %d", &u, &v, &x);

        vertices[u].lista_adj[vertices[u].tamanho] = v;
        vertices[u].distancia = x;
        vertices[u].tamanho++;

        vertices[v].lista_adj[vertices[v].tamanho] = u;
        vertices[v].distancia = x;
        vertices[v].tamanho++;
    }

    scanf("%d", &raiz);

    BFS(vertices, raiz); //Em BFS tem que indicar a raiz

    mostrar(vertices,qtd_vertices);

    printf("\n");

    return 0;
}