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
    int a, b;

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

    printf("\nEscolha um A para saber se ele pertence a sub-árvore de um B escolhido.\n");
    scanf("%d %d", &a, &b);

    if(vertices[a].in > vertices[b].in && vertices[a].out < vertices[b].out)
    {
        printf("\n%d pertence a sub-árvore de %d.\n", a, b);
    }
    else
    {
        printf("\n%d NÃO pertence a sub-árvore de %d.\n", a, b);
    }

    return 0;
}