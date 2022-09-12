#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int list_adj[1000];
    int qtd;
    int cor;
}vertice;

int DFS(vertice *v, int qtd_vertices, int raiz, int cor)
{
    v[raiz].visitado = 1;
    v[raiz].cor = cor;

    for (int i = 0; i < v[raiz].qtd; i++)
    {
        if(v[v[raiz].list_adj[i]].visitado == 0)
        {
            if(!DFS(v,qtd_vertices,v[raiz].list_adj[i],(cor * -1)))
            {
                return 0;
            }
        }
        else
        {
            if(v[raiz].cor == v[v[raiz].list_adj[i]].cor)
            {
                return 0;
            }
        }
    }

    return 1;
}

int main()
{
    int qtd_vertices, qtd_arestas, u, v;
    vertice *vertices;

    scanf("%d %d", &qtd_vertices, &qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0; i < qtd_arestas; i++)
    {
        scanf("%d %d", &u, &v);
        vertices[u].list_adj[vertices[u].qtd] = v;
        vertices[u].qtd++;
        vertices[v].list_adj[vertices[v].qtd] = u;
        vertices[v].qtd++;
    }

    if(DFS(vertices,qtd_vertices,1,1))
    {
        printf("\nGrafo Bipartido!\n");
    }
    else
    {
        printf("\nGrafo NÃO Bipartido!\n");
    }

    return 0;
}