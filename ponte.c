#include <stdio.h>
#include <stdlib.h>

int cont = 0;

typedef struct vertice
{
    int visitado;
    int tamanho;
    int lista_adj[1000];
    int pai;
    int in;
    int lower;
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int *ciclo)
{
    int filho ;

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
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],ciclo);
        }   

        else if(v[raiz].lista_adj[i] != v[raiz].pai) //Achou aresta de retorno
        {
            (*ciclo) = 1;
            if(v[raiz].lower > v[filho].in)
            {
                v[raiz].lower = v[filho].in;
            }
        }

        else if(v[raiz].pai == v[raiz].lista_adj[i])//Vê se está retornando
        {
            if(v[raiz].lower < v[filho].lower)
            {
                v[filho].lower = v[raiz].lower;
            }
        }
    }
    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[filho].lower > v[raiz].in)
        {
            printf("Existe uma ponte entre os vertices %d e %d\n", raiz, v[raiz].lista_adj[i]);
        }
    }
}

int main()
{
    int qtd_vertices, arestas,u , v, ciclo;
    vertice *vertices;

    ciclo = 0;

    scanf("%d %d", &qtd_vertices, &arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0; i < arestas; i++)
    {
        scanf("%d %d", &u, &v);
        vertices[u].lista_adj[vertices[u].tamanho] = v;
        vertices[u].tamanho++;
        vertices[v].lista_adj[vertices[v].tamanho] = u;
        vertices[v].tamanho++;
    }

    DFS(vertices,qtd_vertices,1,&ciclo);

    /*
    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVértice %d: in = %d lower = %d\n", i, vertices[i].in, vertices[i].lower);
    }
    */

    return 0;
}