#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct vertice
{
    int visitado;
    int tamanho;
    int pai;
    int in;
    int low;
    int list_adj[1000];
}vertice;

void DFS(vertice *v, int qtd_vert, int raiz)
{
    int filho;

    if(v[raiz].visitado != 0)
    {
        return;
    }

    v[raiz].visitado = 1;
    v[raiz].in = count;
    v[raiz].low = count;

    count = count + 1;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {
        filho = v[raiz].list_adj[i];

        if(v[filho].visitado == 0)
        {
            v[filho].pai = raiz;

            DFS(v,qtd_vert,filho);

            if(v[filho].low > v[raiz].in)
            {
                printf("Existe ponte entre %d e %d.\n", raiz, filho);
            }

            if(v[raiz].low > v[filho].low)
            {
                v[raiz].low = v[filho].low;
            }
        }
        else if(filho != v[raiz].pai)
        {
            if(v[raiz].low > v[filho].in)
            {
                v[raiz].low = v[filho].in;
            }
        }
    }
}

int main()
{
    int qtd_vert, qtd_ar, u, v;

    scanf("%d %d", &qtd_vert, &qtd_ar);

    vertice *vert = (vertice*)calloc(qtd_vert+1,sizeof(vertice));

    for(int i = 0; i < qtd_ar; i++)
    {
        scanf("%d %d", &u, &v);

        vert[u].list_adj[vert[u].tamanho] = v;
        vert[u].tamanho++;

        vert[v].list_adj[vert[v].tamanho] = u;
        vert[v].tamanho++;
    }

    DFS(vert,qtd_vert,1);

    return 0;
}