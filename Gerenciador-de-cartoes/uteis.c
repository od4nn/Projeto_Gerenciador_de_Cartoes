#include <stdio.h>
#include "DADOS.H"

/*Funcoes uteis para usar durante o programa*/

void tratar_retorno (int codigo, char *msg_sucesso, char *msg_erro) {
    if (codigo == OK) {
        printf("\nSucesso: %s\n", msg_sucesso);
        return;
    }

    printf("\nErro: erro ao %s. ", msg_erro);

    switch (codigo) {
        case ERR_FALTA_MEMORIA: {
            printf("Memoria RAM insuficiente.\n");
            break;
        }
        case ERR_LEITURA: {
            printf("Falha ao salvar dados de clientes.\n");
        }
        default: {
            printf("Erro desconhecido.");
        }
    }
}

void mostrar_menu() {
    printf("\t\n\n=== GESTAO DE CARTOES ===");
    printf("\n1. Adicionar clientes");
    printf("\n2. Listar clientes existentes");
    printf("\n0. Sair");
    printf("\nDigite o numero da opcao escolhida:");
}

void limpar_buffer() {
    while (getchar() != '\n');
}