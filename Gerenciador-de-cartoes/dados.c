#include <stdio.h>
#include <stdlib.h>
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

void adicionar_cliente(BancoDados *b, char *nome);