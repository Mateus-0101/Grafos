#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int tamanho;
    int lista_adj[1000];
    int pai;
}vertice;

void DFS(vertice *v, int qtd_vertices, int raiz, int *ciclo)
{
    if(v[raiz].visitado != 0)
    {
        return;
    }
    
    v[raiz].visitado = 1;

    for(int i = 0; i < v[raiz].tamanho; i++)
    {   
        v[v[raiz].lista_adj[i]].pai = raiz;

        if(v[v[raiz].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[raiz].lista_adj[i],ciclo);
        }   

        if(v[raiz].lista_adj[i] != v[raiz].pai)
        {
            (*ciclo) = 1;
        }
    }
}

int main()
{
    int qtd_insetos, interacoes,u , v, ciclo;
    vertice *insetos;

    int qtd_situacoes = 0; //Somente para teste no site
    scanf("%d", &qtd_situacoes);

    for(int i = 0; i < qtd_situacoes; i++)
    {
        ciclo = 0;

        scanf("%d %d", &qtd_insetos, &interacoes);

        insetos = (vertice*)calloc(qtd_insetos+1,sizeof(vertice));

        for(int i = 0; i < interacoes; i++)
        {
            scanf("%d %d", &u, &v);
            insetos[u].lista_adj[insetos[u].tamanho] = v;
            insetos[u].tamanho++;
            insetos[v].lista_adj[insetos[v].tamanho] = u;
            insetos[v].tamanho++;
        }

        DFS(insetos,qtd_insetos,1,&ciclo);

        printf("Cenário %d:\n", i+1);

        if(ciclo != 0)
        {
            printf("Insetos suspeitos encontrados!\n");
        }
        else
        {
            printf("NÃO foram encontrado insetos suspeitos!\n");
        }
    }

    return 0;
}