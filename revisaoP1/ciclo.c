#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamnaho;
    int pai;
    int lista_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int *ciclo)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;

    for(int i = 0; i < v[raiz].tamnaho; i++)
    {
       v[v[raiz].lista_adj[i]].pai = raiz; //Marca o pai do próximo na lista de adjacência

        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],ciclo);
        }

        //Se elemento da lista de adjacência já foi visitado
        // Mas não é pai, então há ciclo
        if(v[raiz].lista_adj[i] != v[raiz].pai)
        {
            (*ciclo) = 1;
        }
    }
}
int main()
{
    int qtd_vertvices, qtd_arestas, u, v;
    int ciclo = 0;

    scanf("%d %d", &qtd_vertvices, &qtd_arestas);

    vertice *vertices = (vertice*)calloc(qtd_vertvices+1,sizeof(vertice));

    for(int i = 0; i < qtd_arestas; i++)
    {
        scanf("%d %d", &u, &v);

        vertices[u].lista_adj[vertices[u].tamnaho] = v;
        vertices[u].tamnaho++;
        vertices[v].lista_adj[vertices[v].tamnaho] = u;
        vertices[v].tamnaho++;
    }

    DFS(vertices,qtd_vertvices,1,&ciclo);

    if(ciclo != 0)
    {
        printf("\nHá um ciclo, então há uma backedge.\n");
    }
    else
    {
        printf("\nNão há ciclo, não há backedge.\n");

    }

    return 0;
}