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

int adicionar_cliente(BancoDados *b, char *nome, char *digitos,
    char *parceiro, double saldo) {
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

    Cartao *temp = b->clientes[i].cartoes = (Cartao*) malloc(sizeof(Cartao) * 1);

    if (temp == NULL) {
        return ERR_FALTA_MEMORIA;
    }
    b->clientes[i].cartoes[0].id = 1;
    strcpy(b->clientes[i].cartoes[0].ultimos_digitos, digitos);
    strcpy(b->clientes[i].cartoes[0].nome_parceiro, parceiro);
    b->clientes[i].cartoes[0].saldo = saldo;

    b->clientes[i].quant_cartoes = 1;
    b->clientes[i].capacidade_cartoes = 1;

    b->quant_clientes++;

    return OK;
}

int salvar_clientes(BancoDados *b) {
    FILE *f = fopen("dados_clientes.txt", "w");

    if (f == NULL) {
        return ERR_LEITURA;
    }

    for (int i = 0; i < b->quant_clientes; i++) {
        Cliente c = b->clientes[i];

        fprintf(f, "%d;%s;%d\n", c.id, c.nome, c.quant_cartoes);
    }
    fprintf(f,"Fim da lista.\n");

    fclose(f);
    return OK;
}

int carregar_clientes (BancoDados *b) {
    FILE *f = fopen("dados_clientes.txt", "r");

    if (f == NULL) {
        return OK;
    }

    char LINHA[200];
    int id_lixo;
    char NOME_TEMP[TAM_NOME];
    int quant_lixo;

    while (fgets(LINHA, 200, f) != NULL) {
        int status = sscanf(LINHA, "%d;%[^;];%d", &id_lixo,
            NOME_TEMP, &quant_lixo);
        if (status == 3) {
            adicionar_cliente(b, NOME_TEMP, "0000", "Booby", 0.0);
        }
    }
    fclose(f);

    return OK;
}