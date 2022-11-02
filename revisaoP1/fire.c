#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int lista_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int *cont)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    (*cont)++; //Qtd de vértices em componente conectado

    v[raiz].visitado = 1;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],cont);
        }
    }
}

int main()
{
    int qtd_vertice, qtd_arestas, qtd_componentes = 0 ,u, v;
    int *grupo; //qtd de grupos = qtd de líderes = qtd de componentes
    int comb = 1, cont = 0; //comb: combinação total - cont: qtd de vértices em cada componente

    scanf("%d %d", &qtd_vertice, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(qtd_vertice+1,sizeof(vertice));
   // grupo = (int*)calloc(qtd_vertice,sizeof(int));

    for(int i = 0; i < qtd_arestas; i++)
    {
        scanf("%d %d", &u, &v);

        vertices[u].lista_adj[vertices[u].tamanho] = v;
        vertices[u].tamanho++;
        vertices[v].lista_adj[vertices[v].tamanho] = u;
        vertices[v].tamanho++;
    }

    for(int i = 1; i <= qtd_vertice; i++)
    {
        if(vertices[i].visitado == 0)
        {
            DFS(vertices,qtd_vertice,i, &cont);

            grupo[qtd_componentes] = cont;
            qtd_componentes++;
            cont = 0; //reinicia combinação
        }
    }

    for(int i = 0; i < qtd_componentes; i++)
    {
        comb = comb * grupo[i]; //Combinação total = permutação entre os componentes
    }

    printf("\n%d %d \n", qtd_componentes, comb);
    return 0;
}