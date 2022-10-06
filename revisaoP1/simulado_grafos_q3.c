#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int distancia;
    int lista_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int distancia)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;
    v[raiz].distancia = distancia;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],(distancia+1));
        }
    }
}

int main()
{
    int qtd_vertices, qtd_arestas, qtd_consultas, u, v;
    int *consultas, c1, c2;

    scanf("%d", &qtd_vertices);
    scanf("%d", &qtd_arestas);

    vertice *nos = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0; i < qtd_arestas; i++)
    {
        scanf("%d %d", &u, &v);

        nos[u].lista_adj[nos[u].tamanho] = v;
        nos[u].tamanho++;
        nos[v].lista_adj[nos[v].tamanho] = u;
        nos[v].tamanho++;
    }

    scanf("%d", &qtd_consultas);

    for(int i = 1; i <= qtd_consultas; i++)
    {
        scanf("%d %d", &c1, &c2);

        DFS(nos,qtd_vertices,c1,0);

        consultas[i] = nos[c2].distancia;

        for(int j = 1; j <= qtd_vertices; j++)
        {
            nos[j].visitado = 0; //Remarco os vértices como não visitados para poder percorrélos de novo
        }                        //nos DFSs subsequentes, e marcar as distancias corretamente
    }   

    printf("\n");

    for(int i = 1; i <= qtd_consultas; i++)
    {
        printf("%d\n", consultas[i]);
    }

    return 0;
}