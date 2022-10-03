#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int lista_adj[1000];
    int cor;
}vertice;

int DFS(vertice *v, int qtd_vertices, int raiz, int cor)
{
    v[raiz].visitado = 1;
    v[raiz].cor = cor;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            if(!DFS(v,qtd_vertices,v[raiz].lista_adj[i],(cor * -1)))
            {
                return 0; //Se tiver alguma cor igual ligada, o grafo já não é bipartido
            }
        }
        else
        {
            if(v[raiz].cor == v[v[raiz].lista_adj[i]].cor)
            {
                return 0; //Não é bipartido. Ligado a cor igual
            }
        }
    }

    return 1; //É bipartido. Vétices ligados a cores diferentes
}

void mostrar(vertice *v, int qtd_vertices)
{
    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVértice %d: ", i);

        for(int j = 0; j < v[i].tamanho; i++)
        {
            printf("-> ");
            printf("%d ", v[i].lista_adj[j]);
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

    if(DFS(vertices,qtd_vertices,1,1))
    {
        printf("Grafo é bipartido.\n");
    }
    else
    {
        printf("Grafo NÃO é bipartido\n");
    }

    return 0;
}