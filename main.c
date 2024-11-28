#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicão da estrutura de uma conta

typedef struct Conta {
        int numero;
        int agencia;
        float saldo;
        char tipo[10];
        struct Conta *prox;
} Conta;

// Estrutura para gerenciar a fila

typedef struct {
        Conta *inicio;
        Conta *fim;        
}Fila;

// Protótipos das funcões

void iniciarFila(Fila *fila);
int filaVazia(Fila *fila);
void zerarFila(Fila *fila);
void exibirFila(Fila *fila);
void enqueue(Fila *fila, int numero, int agencia, float saldo, char *tipo);
int dequeue(Fila *fila);
void menu(Fila *fila);

//Funcão principal

int main () {
    Fila fila;
    iniciarFila(&fila);
    menu(&fila);
    return 0;
    
}

// Inicializa a FILA
void iniciarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

//Verifica se a fila está vazia

int filaVazia(Fila *fila){
    return fila->inicio == NULL;
    
}

//Zera a fila, liberando memória

void zerarFila(Fila *fila){
    while (!filaVazia(fila)){
        dequeue(fila);
    }
    printf("Fila zerada com sucesso! \n");
}

//Exibe todas as contas da fila

void exibirFila(Fila *fila){
     if(filaVazia(fila)){
        printf("A fila está vazia! \n");
        return;
     }

     Conta *aux = fila->inicio;
     printf("Contas na fila n");
     while (aux != NULL){
           printf("Numero: %d, Agencia: %d, Saldo: %.2f, Tipo: %s\n",
                           aux->numero, aux->agencia, aux->saldo, aux->tipo);
           aux = aux->prox;
     }
     
}

//Adiciona um anova conta na fila

void enqueue(Fila *fila, int numero, int agencia, float saldo, char *tipo) {
    Conta *novaConta = (Conta *)malloc(sizeof(Conta));
    if (novaConta == NULL) {
        printf("Erro ao alocar memória! \n");
        return;
                   
    }

    novaConta->numero = numero;
    novaConta->agencia = agencia;
    novaConta->saldo = saldo;
    strncpy(novaConta->tipo, tipo, 10);
    novaConta->prox = NULL;
     
    if (filaVazia(fila)) {
        fila->inicio = novaConta;
    }else {
        fila->fim->prox = novaConta;
    }
     
    fila->fim = novaConta;
    printf("Conta adicionada com sucesso!\n");
}

// Remove uma conta da fila

int dequeue(Fila *fila) {
    if (filaVazia(fila)) {
        printf("A fila está vazia! Nenhuma conta para remover. \n");
        return 0;
    }
     
    Conta *removida = fila->inicio;
    fila->inicio = fila->inicio->prox;
     
    if(fila->inicio == NULL) {
        fila->fim = NULL;
    }
     
    printf("Conta removida: Numero: %d, Agencia: %d, Saldo: %.2f, Tipo: %s\n",
        removida->numero, removida->agencia, removida->saldo, removida->tipo);
    free(removida);
    return 1;
}

//Menu de opcões

void menu(Fila *fila) {
    int opcao, numero, agencia;
    float saldo;
    char tipo[10];
     
    do {
        printf("\nEscolha a opcão: \n");
        printf("0. Sair\n");
        printf("1. Zerar Fila\n");
        printf("2. Exibir Tela\n");
        printf("3. Enqueue - Inserir Conta\n");
        printf("4. Dequeue - Excluir Conta\n");
        printf("Opcão: ");
        scanf("%d", &opcao);
         
        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                zerarFila(fila);
                break;
            case 2:
                exibirFila(fila);
                break;
            case 3:
                printf("Informe os dados da conta: \n");
                printf("Numero: ");
                scanf("%d", &numero);
                printf("Agencia: ");
                scanf("%d", &agencia);
                printf("Saldo: ");
                scanf("%f", &saldo);
                printf("Tipo(Corrente/Poupanca/Salario): ");
                scanf("%s", tipo);
                enqueue(fila, numero, agencia, saldo, tipo);
                break;
                     
            case 4:
                dequeue(fila);
                break;
                     
            default: 
                printf("Opcão invalida. Tente novamente!\n");
                break;
                         
        }
    }while(opcao !=0);
}



                
     
      
