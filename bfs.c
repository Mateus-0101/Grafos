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
    int *visitado;
    struct lista **lista_adj;
} vertice;

typedef struct fila
{
    int tamanho;
    struct registro *inicio;
    struct registro *final;
} fila;

registro *criar_vertice(int valor)
{
    registro *novo;
    novo = (registro *)calloc(1,sizeof(registro));

    novo->valor = valor;
    novo->prox = NULL;

    return novo;
}

lista *cria_lista()
{
    lista *novo;
    novo = (lista *)calloc(1,sizeof(lista));

    return novo;
}

vertice *criar_grafo(int qtd_vertices)
{
    vertice *grafo;
    grafo = (vertice *)calloc(1,sizeof(vertice));

    grafo->visitado = malloc(qtd_vertices * sizeof(int));
    grafo->lista_adj = malloc(qtd_vertices * sizeof(vertice));

    for(int i = 0; i < qtd_vertices; i++)
    {
        //grafo->lista_adj[i] = 0;
        grafo->visitado[i] = 0;
    }

    return grafo;
}

void criar_aresta(vertice *grafo, int origem, int destino)
{
    registro *novo = criar_vertice(destino);
    novo->prox = grafo->lista_adj[origem];
    grafo->lista_adj[origem] = novo;

    novo = criar_vertice(origem);
    novo->prox = grafo->lista_adj[destino];
    grafo->lista_adj[destino] = novo;
}

fila *criar_fila()
{
    fila *novo;
    novo = (fila *)calloc(1,sizeof(fila));
    return novo;
}

int fila_vazia(fila *f)
{
    if(f->inicio == NULL && f->final == NULL)
    {
        //Fila vazia
        return 1;
    }
    else
    {
        //Fila não vazia
        return 0;
    }
}

void inserir_fila(fila *f, registro *x)
{
    if(f->final == 49)
    {
        printf("\nA fila está cheia.");
    }

    if(fila_vazia(f))
    {
        f->inicio = x;
    }
    else
    {
        f->final->prox = x;
    }

    f->final = x;
    f->tamanho++;
}

int tirar_fila(fila *f)
{
    if(fila_vazia(f))
    {
        return 0;
    }
    else
    {
        int retorno;
        registro *aux;

        aux = f->inicio;
        f->inicio = aux->prox;

        if(f->inicio == NULL)
        {
            //Esvaziando fila por completo
            f->final = NULL; 
        }

        retorno = aux->valor;
        free(aux);
        f->tamanho--;

        return retorno;
    }
}

void BFS(vertice *grafo, int inicial)
{
    fila *f = criar_fila();

    grafo->visitado[inicial] = 1;
    inserir_fila(f,inicial);

    while(!fila_vazia(f))
    {
        int atual = tirar_fila(f);
        printf("Visitado: %d\n", atual);

        registro *aux = grafo->lista_adj[atual];

        while(aux != NULL)
        {
            int adjacente = aux->valor;

            if(grafo->visitado[adjacente] == 0)
            {
                grafo->visitado[adjacente] = 1;
                inserir_fila(f, adjacente);
            }

            aux = aux->prox;
        }
    }
}
int main()
{
    /*
    BFS: acessa todos os vétices mais próximos primeiramente (percorre grafo lateralmente);
    Utiliza da estrutura de fila;
    Enfileira os vétices a serem visitados, que são adjacentes ao vértice atual;
    Retira da fila a medida que forem visitados
    Importante marcar os vértices já visitados para não contá-los mais de uma vez (evitar ciclos).
    Algoritmo muito utilizado para encontrar o caminho mais curto
    */

    vertice *grafo = criar_grafo(4);

    criar_aresta(grafo, 0,1);
    criar_aresta(grafo, 0,2);
    criar_aresta(grafo, 1,2);
    criar_aresta(grafo, 1,3);

    BFS(grafo, 0);
    return 0;
}