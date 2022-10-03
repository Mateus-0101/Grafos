#include <stdio.h>
#include <stdlib.h>

int cont = 0;

typedef struct vertice
{
    int visitado;
    int tamanho;
    int lista_adj[1000];
    int in;
    int out;
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;
    cont++;

    v[raiz].in = cont;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i]);
        }
    }

    cont++;
    v[raiz].out = cont;
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

    DFS(vertices,qtd_vertices,1);

    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVértice %d: Entrada = %d Saída = %d\n", i, vertices[i].in, vertices[i].out);
    }

    return 0;
}