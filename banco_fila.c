#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char tipo;
    char nome[20];
} Cliente;

typedef struct {
    int max;
    int inicio;
    int fim;
    Cliente *itens;
} t_fila;

t_fila *createFila(int n) {
    t_fila *f = (t_fila *)malloc(sizeof(t_fila));
    f->max = n;
    f->itens = (Cliente *)malloc(sizeof(Cliente) * n);
    f->inicio = 0;
    f->fim = 0;
    return f;
}

void destroyFila(t_fila *f) {
    free(f->itens);
    free(f);
}

int isEmptyFila(t_fila *f) {
    return f->inicio == f->fim;
}

void inFila(t_fila *f, Cliente x) {
    f->itens[f->fim] = x;
    f->fim = (f->fim + 1) % f->max;
}

int outFila(t_fila *f, Cliente *x) {
    if (!isEmptyFila(f)) {
        *x = f->itens[f->inicio];
        f->inicio = (f->inicio + 1) % f->max;
        return 1;
    }
    return 0;
}

void clearFila(t_fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

void print(t_fila *f) {
    int i;
    for (i = f->inicio; i != f->fim; i = (i + 1) % f->max) {
        printf("%c: %s\n", f->itens[i].tipo, f->itens[i].nome);
    }
    printf("\n");
}

int main() {
    t_fila *filaGeral = createFila(10);
    t_fila *filaPrioridade = createFila(10);
    t_fila *filaAtendidos = createFila(20);

    char comando;
    int contadorPrioridade = 0;
    int contadorGeral = 0;
    Cliente cliente;

    while (1) {
        printf("\n------ Menu do Banco ------\n");
        printf("1. Adicionar novo cliente (Digite 'p' para prioridade ou 'g' para geral)\n");
        printf("2. Chamar próximo cliente (Digite 's')\n");
        printf("3. Finalizar expediente (Digite 'f')\n");
        printf("Digite sua escolha: ");
        scanf(" %c", &comando);

        if (comando == 'g' || comando == 'p') {
            Cliente novoCliente;
            novoCliente.tipo = comando;
            printf("\nDigite o nome do cliente: ");
            scanf("%s", novoCliente.nome);
            if (novoCliente.tipo == 'p') {
                inFila(filaPrioridade, novoCliente);
            } else if (novoCliente.tipo == 'g') {
                inFila(filaGeral, novoCliente);
            } else {
                printf("\nTipo de cliente inválido.\n");
            }

        } else if (comando == 'f') {
            printf("\nTodos os atendimentos realizados: \n");
            print(filaAtendidos);
            break;
        } else if (comando == 's') {
            if (!isEmptyFila(filaPrioridade) && contadorPrioridade < 3) {
                outFila(filaPrioridade, &cliente);
                inFila(filaAtendidos, cliente);
                contadorPrioridade++;
                contadorGeral = 0;
                printf("Cliente atendido: %c: %s\n", cliente.tipo, cliente.nome);
            } else if (!isEmptyFila(filaGeral)) {
                outFila(filaGeral, &cliente);
                inFila(filaAtendidos, cliente);
                contadorGeral++;
                contadorPrioridade = 0;
                printf("Cliente atendido: %c: %s\n", cliente.tipo, cliente.nome);
            } else if (!isEmptyFila(filaPrioridade)) {
                outFila(filaPrioridade, &cliente);
                inFila(filaAtendidos, cliente);
                contadorPrioridade++;
                contadorGeral = 0;
                printf("Cliente atendido: %c:  %s\n", cliente.tipo, cliente.nome);
            } else {
                printf("Nenhuma fila disponível.\n");
            }
        } else {
            printf("Comando inválido.\n");
        }
    }
    destroyFila(filaGeral);
    destroyFila(filaPrioridade);
    destroyFila(filaAtendidos);

    return 0;
}

