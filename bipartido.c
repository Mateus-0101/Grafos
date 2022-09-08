#include <stdio.h>
#include <stdlib.h>

int bandeira = 0;

typedef struct vertices
{
    int visitado;
    int cor;
    int lista_adj[100];
    int tamanho;
} vertices;

void DFS(vertices *v, int qtd_vertices, int raiz)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i]);

            if(v[v[raiz].lista_adj[i]].cor == v[v[raiz].lista_adj[i+1]].cor)
            {
                bandeira = 1;
            }
        }
    }
}

int main()
{
    int qtd_vertices, qtd_arestas, u, v;

    scanf("%d", &qtd_vertices);
    
    vertices *vertice = (vertices*)calloc(qtd_vertices+1,sizeof(vertices));

    for(int i = 0; i < qtd_vertices; i++)
    {
        scanf("%d %d", &u, &v);
        vertice[u].lista_adj[vertice[u].tamanho] = v;
        vertice[u].lista_adj[vertice[u].cor] = 0;
        vertice[u].tamanho++;
        vertice[v].lista_adj[vertice[v].tamanho] = u;
        vertice[v].lista_adj[vertice[v].cor] = 1;
        vertice[v].tamanho++;
    }

    DFS(vertice,qtd_vertices,1);

    if(bandeira == 1)
    {
        printf("O grafo não é bipartido.\n");
    }
    else
    {
        printf("Grafo é bipartido\n");
    }

    return 0;
}