#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dados.h"

BancoDados* inicializar_banco() {
    BancoDados *b = (BancoDados*) malloc(sizeof(BancoDados));

    if (b == NULL) {
        printf("Erro ao alocar memoria!");
        exit(ERR_FALTA_MEMORIA);
    }

    b->quant_clientes = 0;
    b->capacidade_clientes = 0;

    b-> clientes = NULL;
    return b;
}

void adicionar_cliente(BancoDados *b, char *nome) {
    if (b->capacidade_clientes == 0) {
        b = (BancoDados*) realloc(b, sizeof(BancoDados) * (b->capacidade_clientes += 10));
    }
    if (b->quant_clientes == b->capacidade_clientes) {
        b = (BancoDados*) realloc(b, sizeof(BancoDados) * (b->capacidade_clientes *= 2));
    }

    //copiar b->clientes[b->quant_clientes].nome para onde??
    b->clientes->id = b->quant_clientes + 1; //provavelmente algo assim?
    b->clientes->cartoes = NULL; //assim talvez? deve ta faltando falar qual o indice do cliente
    b->quant_clientes++;
}