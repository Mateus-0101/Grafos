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

void mostrar(vertice *v, int qtd_vertices)
{
    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVertices %d: ", i);

        for(int j = 0; j < v[i].tamanho; j++)
        {
            printf("-> %d (%d) ", v[i].lista_adj[j].vertice, v[i].lista_adj[j].peso);
        }
    }
}

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
    int qtd_vertices, qtd_arestas, u, v, x;
    int infinito = 99999;
    aresta ast;

    //scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(15,sizeof(vertice));

    ast.peso = 6;
    ast.vertice = 2;
    vertices[1].lista_adj[vertices[1].tamanho] = ast;
    vertices[1].distancia = infinito;
    vertices[1].tamanho++;

    ast.vertice = 1;
    vertices[2].lista_adj[vertices[2].tamanho] = ast;
    vertices[2].distancia = infinito;
    vertices[2].tamanho++;

    ast.peso = 9;
    ast.vertice = 3;
    vertices[1].lista_adj[vertices[1].tamanho] = ast;
    vertices[1].distancia = infinito;
    vertices[1].tamanho++;

    ast.vertice = 1;
    vertices[3].lista_adj[vertices[3].tamanho] = ast;
    vertices[3].distancia = infinito;
    vertices[3].tamanho++;

    ast.peso = 11;
    ast.vertice = 4;
    vertices[1].lista_adj[vertices[1].tamanho] = ast;
    vertices[1].distancia = infinito;
    vertices[1].tamanho++;

    ast.vertice = 1;
    vertices[4].lista_adj[vertices[4].tamanho] = ast;
    vertices[4].distancia = infinito;
    vertices[4].tamanho++;

    ast.peso = 5;
    ast.vertice = 5;
    vertices[1].lista_adj[vertices[1].tamanho] = ast;
    vertices[1].distancia = infinito;
    vertices[1].tamanho++;

    ast.vertice = 1;
    vertices[5].lista_adj[vertices[5].tamanho] = ast;
    vertices[5].distancia = infinito;
    vertices[5].tamanho++;

    ast.peso = 9;
    ast.vertice = 6;
    vertices[1].lista_adj[vertices[1].tamanho] = ast;
    vertices[1].distancia = infinito;
    vertices[1].tamanho++;

    ast.vertice = 1;
    vertices[6].lista_adj[vertices[6].tamanho] = ast;
    vertices[6].distancia = infinito;
    vertices[6].tamanho++;

    ast.peso = 3;
    ast.vertice = 3;
    vertices[2].lista_adj[vertices[2].tamanho] = ast;
    vertices[2].distancia = infinito;
    vertices[2].tamanho++;

    ast.vertice = 2;
    vertices[3].lista_adj[vertices[3].tamanho] = ast;
    vertices[3].distancia = infinito;
    vertices[3].tamanho++;

    ast.peso = 6;
    ast.vertice = 4;
    vertices[2].lista_adj[vertices[2].tamanho] = ast;
    vertices[2].distancia = infinito;
    vertices[2].tamanho++;

    ast.vertice = 2;
    vertices[4].lista_adj[vertices[4].tamanho] = ast;
    vertices[4].distancia = infinito;
    vertices[4].tamanho++;

    ast.peso = 5;
    ast.vertice = 5;
    vertices[2].lista_adj[vertices[2].tamanho] = ast;
    vertices[2].distancia = infinito;
    vertices[2].tamanho++;

    ast.vertice = 2;
    vertices[5].lista_adj[vertices[5].tamanho] = ast;
    vertices[5].distancia = infinito;
    vertices[5].tamanho++;

    ast.peso = 2;
    ast.vertice = 6;
    vertices[2].lista_adj[vertices[2].tamanho] = ast;
    vertices[2].distancia = infinito;
    vertices[2].tamanho++;

    ast.vertice = 2;
    vertices[6].lista_adj[vertices[6].tamanho] = ast;
    vertices[6].distancia = infinito;
    vertices[6].tamanho++;

    ast.peso = 4;
    ast.vertice = 5;
    vertices[3].lista_adj[vertices[3].tamanho] = ast;
    vertices[3].distancia = infinito;
    vertices[3].tamanho++;

    ast.vertice = 3;
    vertices[5].lista_adj[vertices[5].tamanho] = ast;
    vertices[5].distancia = infinito;
    vertices[5].tamanho++;

    ast.peso = 4;
    ast.vertice = 5;
    vertices[3].lista_adj[vertices[3].tamanho] = ast;
    vertices[3].distancia = infinito;
    vertices[3].tamanho++;

    ast.vertice = 3;
    vertices[6].lista_adj[vertices[6].tamanho] = ast;
    vertices[6].distancia = infinito;
    vertices[6].tamanho++;

    ast.peso = 5;
    ast.vertice = 5;
    vertices[4].lista_adj[vertices[4].tamanho] = ast;
    vertices[4].distancia = infinito;
    vertices[4].tamanho++;

    ast.vertice = 4;
    vertices[5].lista_adj[vertices[5].tamanho] = ast;
    vertices[5].distancia = infinito;
    vertices[5].tamanho++;

    ast.peso = 6;
    ast.vertice = 6;
    vertices[4].lista_adj[vertices[4].tamanho] = ast;
    vertices[4].distancia = infinito;
    vertices[4].tamanho++;

    ast.vertice = 4;
    vertices[6].lista_adj[vertices[6].tamanho] = ast;
    vertices[6].distancia = infinito;
    vertices[6].tamanho++;

    ast.peso = 8;
    ast.vertice = 6;
    vertices[5].lista_adj[vertices[5].tamanho] = ast;
    vertices[5].distancia = infinito;
    vertices[5].tamanho++;

    ast.vertice = 5;
    vertices[6].lista_adj[vertices[6].tamanho] = ast;
    vertices[6].distancia = infinito;
    vertices[6].tamanho++;

    dijkstra(vertices,6);

    mostrar(vertices,6);

    printf("\n");

    return 0;
}