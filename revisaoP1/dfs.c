#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int lista_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz)
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
    int qtd_vertices, qtd_arestas, u, v;

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

    mostrar(vertices,qtd_vertices);

    printf("\n");
    return 0;
}