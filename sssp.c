#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int distancia;
    int lista_adj[100];
    int tamanho;
}vertice;

void DFS(vertice *v , int qtd_vertices, int origem, int distancia)
{
    if(v[origem].visitado != 0)
    {
        return;
    }

    v->distancia = 0;

    v[origem].visitado = 1;
    v[origem].distancia = distancia;

    for(int i = 0; i < v[origem].tamanho; i++)
    {
        if(v[v[origem].lista_adj[i]].visitado == 0)
        {
            DFS(v,qtd_vertices,v[origem].lista_adj[i], distancia+1);
        }
    }
}

int main()
{
    int qtd_cidades, estradas, u, v, qtd_garotas, morada;
    int garotas[100];
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

    DFS(cidade,qtd_cidades,1,0);

    printf("Defina a quantidade de garotas: ");
    scanf("%d", &qtd_garotas);

    for(int i = 0; i < qtd_garotas; i++)
    {
        printf("Difina a cidade que a garota %d mora: ", i+1);
        scanf("%d", &garotas[i]);
    }

    int id_escolhida = garotas[0];

    for(int i = 0; i < qtd_garotas; i++)
    {
        if(cidade[garotas[i]].distancia < cidade[id_escolhida].distancia)
        {
            id_escolhida = garotas[i];
        }
        else
        {
            if(cidade[garotas[i]].distancia == cidade[id_escolhida].distancia)
            {
                if(garotas[i] < id_escolhida)
                {
                    id_escolhida = garotas[i];
                }
            }
        }
    }

    printf("A garota mais próxima está na cidade %d\n", id_escolhida);

    return 0;
}