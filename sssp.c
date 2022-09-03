#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int distancia;
    int lista_adj[100];
    int tamanho;
}vertice;

void DFS(vertice *v , int qtd_vertices, int origem)
{
    if(v[origem].visitado != 0)
    {
        return;
    }

    v->distancia = 0;

    v[origem].visitado = 1;

    for(int i = 0; i < v[origem].tamanho; i++)
    {
        if(v[v[origem].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[origem].lista_adj[i]);
            v->distancia++;
        }
    }
}

int main()
{
    int qtd_cidades, estradas, u, v, garotas, morada;
    vertice *cidade;

    printf("Defina a  quantidade de cidades: ");
    scanf("%d", &qtd_cidades);

    cidade = (vertice*)calloc(qtd_cidades,sizeof(vertice));

    estradas = qtd_cidades - 1;

    for(int i = 0; i < estradas; i++)
    {
        printf("Defina as cidades a e b ligadas por uma estrada: ");
        scanf("%d %d", &u, &v);
        cidade[u].lista_adj[cidade[u].tamanho] = v;
        cidade[u].tamanho++;
        cidade[v].lista_adj[cidade[v].tamanho]= u;
        cidade[v].tamanho++;
    }

    printf("Defina a quantidade de garotas: ");
    scanf("%d", &garotas);

    for(int i = 0; i < garotas; i++)
    {
        printf("Difina a cidade que a garota %d mora: ", i+1);
        scanf("%d", &morada);

        cidade[morada].lista_adj;
    }

    for(int i = 0; i < qtd_cidades; i++)
    {
        if(cidade[i].visitado == 0)
        {
            DFS(cidade,qtd_cidades,1);
        }
    }

    int menor = 1;

    for(int i = 0; i < qtd_cidades; i++)
    {
        if(menor > cidade[i].distancia)
        {
            menor = cidade[i].distancia;
        }
    }

    printf("A garota mais próxima está na cidade %d\n", menor);

    return 0;
}