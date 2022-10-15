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

void DFS(vertice *v, int qtd_vertices, int raiz)
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
            DFS(v,qtd_vertices,v[raiz].lista_adj[i]);

            //Lógica da ponte
            if(v[filho].lower > v[raiz].in)
            {
                printf("Existe uma ponte entre os vertices %d e %d\n", raiz, v[raiz].lista_adj[i]);
            }
            //Calibra lower
            if(v[raiz].lower > v[filho].lower)
            {
                v[raiz].lower = v[filho].lower;
            }
        }   
        else if(v[raiz].lista_adj[i] != v[raiz].pai) //Já visitado: Há aresta de retorno ?
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
    int qtd_vertices, arestas,u , v;
    vertice *vertices;

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

    DFS(vertices,qtd_vertices,1);

    /*
    for(int i = 1; i <= qtd_vertices; i++)
    {
        printf("\nVértice %d: in = %d lower = %d\n", i, vertices[i].in, vertices[i].lower);
    }
    */

    return 0;
}