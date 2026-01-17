#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dados.h"

BancoDados* inicializar_banco() {
    BancoDados *b = (BancoDados*) malloc(sizeof(BancoDados));

    if (b == NULL) {
        printf("Erro Critico: Sem memoria para inicializar o programa!");
        exit(ERR_FALTA_MEMORIA);
    }

    b->quant_clientes = 0;
    b->capacidade_clientes = 0;

    b-> clientes = NULL;
    return b;
}

int adicionar_cliente(BancoDados *b, char *nome) {
    if (b->quant_clientes == b->capacidade_clientes) {
        int nova_capacidade = (b->capacidade_clientes == 0) ? 10 : (b->capacidade_clientes * 2);

        //variavel temp, pq se der NULL a variavel original nao se perde
        Cliente *temp = (Cliente*) realloc(b->clientes, sizeof(Cliente) * nova_capacidade);

        if (temp == NULL) {
            printf("Erro Critico: Sem memoria para expandir clientes!\n");
            return(ERR_FALTA_MEMORIA);
        }

        //se der certo o endereço de clientes se atualiza
        b->clientes = temp;
        b->capacidade_clientes = nova_capacidade;
    }

    int i = b->quant_clientes;

    b->clientes[i].id = i + 1;
    strcpy(b->clientes[i].nome, nome);

    //inicializar variaveis com zero por segurança
    b->clientes[i].cartoes = NULL;
    b->clientes[i].quant_cartoes = 0;
    b->clientes[i].capacidade_cartoes = 0;

    b->quant_clientes++;

    return OK;
}