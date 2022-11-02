#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int distancia;
    int lista_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int distancia)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;
    v[raiz].distancia = distancia;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],(distancia+1));
        }
    }
}

int main()
{
    int qtd_vertice, qtd_arestas, u, v;
    int prox = 0, dist = 0; //Raíz do segundo DFS e distância

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

    DFS(vertices,qtd_vertice,1,0);

    for(int i = 1; i <= qtd_vertice; i++)
    {
        if(vertices[i].distancia > dist)
        {
            prox = i; //Encontrando o vértice com a maior distância
            dist = vertices[i].distancia;
        }

        vertices[i].distancia = 0;
        vertices[i].visitado = 0;
    }

    DFS(vertices,qtd_vertice,prox,0);

    for(int i = 1; i <= qtd_vertice; i++)
    {
        if(vertices[i].distancia > dist)
        {
            prox = i;
            dist = vertices[i].distancia; //Encontrando a maior distância
        }
    }

    printf("\nDiâmetro do grafo: %d\n", dist);

    return 0;
}