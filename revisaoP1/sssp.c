#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int lista_adj[1000];
    int distancia;
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
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],distancia+1);
        }
    }
}

void mostrar(vertice *v, int qtd_vertices)
{
    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVértice: %d ", i);

        for(int j = 0; j < v[i].tamanho; j++)
        {
            printf("-> ");
            printf("%d ",v[i].lista_adj[j]);
        }
    }
}

int main()
{
    int qtd_vertices, qtd_arestas, qtd_garotas, u, v;
    int garotas[1000];

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

    DFS(vertices,qtd_vertices,1,0); //DFS para descobrir as distâncias

    scanf("%d", &qtd_garotas);

    for(int i = 0; i < qtd_garotas; i++)
    {
        scanf("%d", &garotas[i]); //Cidade que determinada garota vive
    }

    int id_escolhida = garotas[0];

    for( int i = 0; i < qtd_garotas; i++)
    {
        if(vertices[garotas[i]].distancia < vertices[id_escolhida].distancia)
        {
            id_escolhida = garotas[i];
        }
        else
        {
            if(vertices[garotas[i]].distancia == vertices[id_escolhida].distancia)
            {
                if(garotas[i] < id_escolhida)
                {
                    id_escolhida = garotas[i]; //Se forem iguais, mostra o de menor valor nominal
                }
            }
        }
    }

    printf("\nId escolhida: %d\n", id_escolhida);

    return 0;
}