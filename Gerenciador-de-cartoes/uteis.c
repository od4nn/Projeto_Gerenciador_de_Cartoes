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
        default: {
            printf("Erro desconhecido.");
        }
    }
}