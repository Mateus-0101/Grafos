#include <stdio.h>
#include <stdlib.h>

int cont = 0;

typedef struct vertice
{
    int tamanho;
    int visitado;
    int pai;
    int in;
    int lower;
    int lista_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz)
{
    int filho;

    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;
    v[raiz].in = cont;
    v[raiz].lower = cont;

    cont = cont + 1;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        filho = v[raiz].lista_adj[i];

        if(v[filho].visitado == 0)
        {
            v[filho].pai = raiz;
            DFS(v,qtd_vertices,v[raiz].lista_adj[i]); //Percorre lista do vértice

            if(v[filho].lower > v[raiz].in) //Encontra ponte
            {
                printf("A estrada que conecta as cidades %d e %d não pode entrar em reforma.\n", raiz,v[raiz].lista_adj[i]);
            }

            if(v[raiz].lower > v[filho].lower) //Calibra Lower: pega o menor valor
            {
                v[raiz].lower = v[filho].lower;
            }
        }
        else if(v[raiz].lista_adj[i] != v[raiz].pai) //Já visitado mas não pelo pai -> ciclo/backedge : não pode ser ponte
        {
            if(v[raiz].lower > v[filho].in)
            {
                v[raiz].lower = v[filho].in;
            }
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

    DFS(vertices,qtd_vertices,1);

    return 0;
}