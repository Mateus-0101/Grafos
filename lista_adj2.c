#include <stdio.h>
#include <stdlib.h>
 
// Define o número máximo de vértices no gráfico
//#define N 6
 
// Estrutura de dados para armazenar um objeto gráfico
struct Graph
{
    // Um array de ponteiros para Node para representar uma lista de adjacências
    struct Node* head[100];
};
 
// Estrutura de dados para armazenar nós da lista de adjacências do gráfico
struct Node
{
    int dest;
    struct Node* next;
};
 
// Estrutura de dados para armazenar uma aresta do gráfico
struct Edge {
    int src, dest;
};
 
// Função para criar uma lista de adjacências a partir de arestas especificadas
struct Graph* createGraph(struct Edge edges[], int n)
{
    // aloca armazenamento para a estrutura de dados do gráfico
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
 
    // inicializa o ponteiro de cabeça para todos os vértices
    for (int i = 0; i < N; i++) {
        graph->head[i] = NULL;
    }
 
    // adiciona arestas ao grafo direcionado uma a uma
    for (int i = 0; i < n; i++)
    {
        // obtém o vértice de origem e destino
        int src = edges[i].src;
        int dest = edges[i].dest;
 
        // 1. aloca um novo nó da lista de adjacências de src para dest
 
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->dest = dest;
 
        // aponta novo nó para a cabeça atual
        newNode->next = graph->head[src];
 
        // aponta o ponteiro principal para o novo nó
        graph->head[src] = newNode;
 
        // 2. aloca um novo nó da lista de adjacências de `dest` para `src`
 
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->dest = src;
 
        // aponta novo nó para a cabeça atual
        newNode->next = graph->head[dest];
 
        // altera o ponteiro de cabeça para apontar para o novo nó
        graph->head[dest] = newNode;
    }
 
    return graph;
}
 
// Função para imprimir a representação da lista de adjacências de um gráfico
void printGraph(struct Graph* graph)
{
    for (int i = 0; i < N; i++)
    {
        // imprime o vértice atual e todos os seus vizinhos
        struct Node* ptr = graph->head[i];
        while (ptr != NULL)
        {
            printf("(%d —> %d)\t", i, ptr->dest);
            ptr = ptr->next;
        }
 
        printf("\n");
    }
}
 
// Implementação de grafos direcionados em C
int main(void)
{
    int pares;
    
    // array de entrada contendo arestas do gráfico (conforme o diagrama acima)
    // (x, y) par no array representa uma aresta de x a y
    struct Edge edges[] =
    {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    };
 
    // calcula o número total de arestas
    int n = sizeof(edges)/sizeof(edges[0]);
 
    // constrói um gráfico a partir das arestas dadas
    struct Graph *graph = createGraph(edges, n);
 
    // Função para imprimir a representação da lista de adjacências de um gráfico
    printGraph(graph);
 
    return 0;
}