#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int distancia;
    int lista_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int distancia, int *prox)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;
    v[raiz].distancia = distancia;
    (*prox) = raiz;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],(distancia+1),prox);
        }
    }
}

int main()
{
    int qtd_vertice, qtd_arestas, u, v;
    int prox; //Raíz do segundo DFS

    scanf("%d %d", &qtd_vertice, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(qtd_vertice+1,sizeof(vertice));

    for(int i = 1; i <= qtd_arestas; i++)
    {
        scanf("%d %d", &u, &v);

        vertices[u].lista_adj[vertices[u].tamanho] = v;
        vertices[u].tamanho++;
        vertices[v].lista_adj[vertices[v].tamanho] = u;
        vertices[v].tamanho++;
    }

    DFS(vertices,qtd_vertice,1,0,&prox);

    for(int i = 1; i <= qtd_vertice; i++)
    {
        vertices[i].visitado = 0; //Remarco os vértices como não visitados para poder percorrélos de novo
    }

    if(vertices[1].tamanho > 1) //Caso o primeiro vértice esteja conectado a mais de um elemento
    {
        DFS(vertices,qtd_vertice,prox,vertices[prox].distancia,&prox);
    }

    printf("\nDiâmetro do grafo: %d\n", vertices[prox].distancia);

    return 0;
}