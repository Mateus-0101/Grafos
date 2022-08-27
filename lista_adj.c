#include <stdio.h>
#include <stdlib.h>

typedef struct no //Define estrutura dos nós 
{
    int valor;
    struct no *prox, *ant;
}no;

typedef struct lista //Define estrutura da Lista
{
    no *inicio, *fim;
    int tam;
}lista;

lista *alocar_lista() //Função para alocar lista na memória
{
    lista *novo;
    novo = (lista*)malloc(sizeof(lista));

    novo -> tam = 0;
    novo -> inicio = NULL;
    novo -> fim = NULL;

    return novo;
}

no *cria_no()
{
    no *novo = (no*)malloc(sizeof(no)); //cria os nós, e aloca na memória
    novo -> valor = 0;
    novo -> prox = NULL;
    novo->ant = NULL;

    return novo;
}

void inserir_lista(lista *lista, int valor1, int valor2)
{
    no *no1 = cria_no();
    no *no2 = cria_no();
    no *aux = NULL;

    no1->valor = valor1;
    no2->valor = valor2;

    if(lista -> inicio == NULL) //Caso lista esteja vazia
    {
        lista -> inicio = no1;
    }
    else //Ligação dos pares (multidirecional)
    {
        lista->fim = no2;
        no1->prox = no2;
        no2->ant = no1;

    }
    lista->tam++;
}

void mostrar_lista(lista *lista) 
{
    no *inicio = lista -> inicio;

    if(lista->inicio == NULL)
    {
        printf("A lista está vazia.\n");
    }
    while(inicio != NULL)
    {
        printf("%d ", inicio -> valor);
        inicio = inicio -> prox;
    }
    printf("\n");
}

int main()
{
    lista list_adj;
    int pares, p1, p2; //numero de pares e seus valores respectivos

    printf("Insira o número de pares: ");
    scanf("%d", &pares);

    for(int i = 0; i < pares; i++)
    {
        printf("Insira o primeiro número do par %d: ", i+1);
        scanf("%d %d", &p1, &p2);

        inserir_lista(&list_adj, p1, p2);
    }
    
    mostrar_lista(&list_adj);
    printf("\n");
    
    return 0;

}