#include <stdio.h>
#include <stdlib.h>

typedef struct registro
{
    int valor;
    struct registro *prox;
} registro;

typedef struct lista
{
    int qtd;
    struct registro *inicio;
}lista;

typedef struct vertice
{
    int visitado;
    struct lista *lista_adj;
}vertice;

lista *cria_lista()
{
    lista *novo = (lista*)calloc(1,sizeof(lista));
    return novo;
}

registro *cria_registro()
{
    registro *novo = (registro*)calloc(1,sizeof(registro));
    return novo;
}

vertice *cria_vertice(int qtd)
{
    vertice *novo = (vertice*)calloc(qtd+1,sizeof(vertice)); //Pq 1000 ?
    return novo;
}

void inserir_lista(lista *l, int valor) //Insere do forma ordenada
{
    if(l == NULL)
    {
        return;
    }

    registro *novo, *aux = NULL, *ant = NULL;

    novo = cria_registro();
    novo->valor = valor;

    if(l->inicio == NULL)
    {
        l->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = l->inicio;

        while(aux != NULL && !inserido)
        {
            if(aux->valor == novo->valor)
            {
                return;
            }
            if(aux->valor < novo->valor)
            {
                ant = aux;
                aux = aux->prox;
            }
            else
            {
                if(ant == NULL)
                {
                    l->inicio = novo;
                }
                else
                {
                    ant->prox = novo;
                }

                novo->prox = aux;
                inserido = 1;
            }
        }

        if(!inserido)
        {
            ant->prox = novo;
            inserido = 1;
        }
    }

    l->qtd++;
    return;
}

void DFS(vertice *v, int valor, int *comb)
{
    registro *aux;

    if(v[valor].visitado == 1)
    {
        return;
    }

    (*comb)++; //Conta qtd de vértices em componente conectado

    v[valor].visitado = 1;

    if(v[valor].lista_adj == NULL)
    {
        return;
    }

    aux = v[valor].lista_adj->inicio;

    while(aux != NULL)
    {
        if(v[aux->valor].visitado == 0)
        {
            DFS(v,aux->valor,comb);
        }

        aux = aux->prox;
    }
}

int main()
{
    int *qtd_lideres, qtd_arestas, qtd_vertices, u = 0, v = 0;
    vertice *vertices;

    int qtd_situacoes = 0; //Somente para teste no site
    scanf("%d", &qtd_situacoes);

    for(int i = 0; i < qtd_situacoes; i++) //Somente para teste no site
    {
        scanf("%d %d", &qtd_vertices, &qtd_arestas);
        qtd_lideres = (int*)calloc(qtd_vertices,sizeof(int));

        vertices = cria_vertice(qtd_vertices);

        for(int i = 0; i < qtd_arestas; i++)
        {
            scanf("%d %d", &u, &v);

            if(vertices[u].lista_adj == NULL)
            {
                vertices[u].lista_adj = cria_lista();
            }

            inserir_lista(vertices[u].lista_adj,v);

            if(vertices[v].lista_adj == NULL)
            {
                vertices[v].lista_adj = cria_lista();
            }

            inserir_lista(vertices[v].lista_adj,u);
        }

        int cont = 0, comb = 0;

        for(int i = 1; i <= qtd_vertices; i++)
        {
            if(vertices[i].visitado == 0)
            {
                DFS(vertices,i,&comb);

                qtd_lideres[cont] = comb; //Qtd de vértices a cada componente
                cont++;                   //em cada índice do vetor de líderes
                comb = 0;
            }
        }

        int combTotal = 1;

        for(int i = 0; i < cont; i++)
        {
            combTotal = combTotal * qtd_lideres[i];
        }

        printf("\n%d %d\n\n", cont, combTotal);
    }

    return 0;
}