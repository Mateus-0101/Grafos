#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int list_adj[1000];
    int distancia;
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int distancia, int *cont)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;
    v[raiz].distancia = distancia;

    (*cont) = raiz;
    /*
    printf("raiz final: %d\n", raiz);
    printf("distancia: %d\n", v[raiz].distancia);
    */
    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].list_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].list_adj[i],(distancia+1),cont);
        }
    }
}
int main()
{
    int qtd_vertices, u, v;
    int raiz;

    scanf("%d", &qtd_vertices);

    vertice *vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 1; i <= qtd_vertices-1; i++)
    {
        scanf("%d %d", &u, &v);

        vertices[u].list_adj[vertices[u].tamanho] = v;
        vertices[u].tamanho++;
        vertices[v].list_adj[vertices[v].tamanho] = u;
        vertices[v].tamanho++;
    }

    DFS(vertices,qtd_vertices,1,0,&raiz);

    for(int i = 1; i <= qtd_vertices; i++) //Retirando visitado para poder refazer o DFS
    {
        vertices[i].visitado = 0;
    }

    if(vertices[1].tamanho > 1) //Para caso haja mais de 1 aresta ligada ao primeiro vértice inserido
    {
        DFS(vertices,qtd_vertices,raiz,vertices[raiz].distancia,&raiz);
    }

    //printf("Raiz longe: %d\n", raiz);
    printf("\n%d\n", vertices[raiz].distancia);

    return 0;
}