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

        fprintf(f, "%d;%s;%d;%s;%s;%.2lf\n",
            c.id, c.nome, c.quant_cartoes, c.cartoes[0].ultimos_digitos,
            c.cartoes[0].nome_parceiro, c.cartoes[0].saldo);
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

    char LINHA[300];
    int id_lixo, quant_lixo;
    char NOME_TEMP[TAM_NOME];
    char DIGITOS_TEMP[TAM_DIGITOS];
    char PARCEIRO_TEMP[TAM_PARCEIRO];
    double SALDO_TEMP;


    while (fgets(LINHA, 300, f) != NULL) {
        LINHA[strcspn(LINHA, "\n")] = 0;

        int status = sscanf(LINHA, "%d;%[^;];%d;%[^;];%[^;];%lf",
            &id_lixo, NOME_TEMP, &quant_lixo,
            DIGITOS_TEMP, PARCEIRO_TEMP, &SALDO_TEMP);
        if (status == 6) {
            adicionar_cliente(b, NOME_TEMP, DIGITOS_TEMP, PARCEIRO_TEMP, SALDO_TEMP);
        }
    }
    fclose(f);

    return OK;
}

int adicionar_cartao_extra(BancoDados *b, int id_cliente, char *digitos, char *parceiro, double saldo) {

    // CORREÇÃO AQUI: Primeiro achamos o índice correto
    int indice = buscar_indice_cliente(b, id_cliente);

    if (indice == ERR_CLIENTE_NAO_ENCONTRADO) {
        return ERR_CLIENTE_NAO_ENCONTRADO;
    }

    // Agora sim usamos o índice para apontar
    Cliente *alvo = &b->clientes[indice];

    // 2. VERIFICA CAPACIDADE (Do bolso do cliente)
    if (alvo->quant_cartoes == alvo->capacidade_cartoes) {
        int nova_capacidade = alvo->capacidade_cartoes * 2;

        Cartao *temp = (Cartao*) realloc(alvo->cartoes, sizeof(Cartao) * nova_capacidade);

        if (temp == NULL) return ERR_FALTA_MEMORIA;

        alvo->cartoes = temp;
        alvo->capacidade_cartoes = nova_capacidade;
    }

    // 3. ADICIONA O NOVO CARTÃO
    int i = alvo->quant_cartoes;

    alvo->cartoes[i].id = i + 1;
    strcpy(alvo->cartoes[i].ultimos_digitos, digitos);
    strcpy(alvo->cartoes[i].nome_parceiro, parceiro);
    alvo->cartoes[i].saldo = saldo;

    // 4. ATUALIZA CONTADORES
    alvo->quant_cartoes++;

    return OK;
}

int alterar_dados_cliente(BancoDados *b, int id_cliente) {

    int indice = buscar_indice_cliente(b, id_cliente);

    if (indice == ERR_CLIENTE_NAO_ENCONTRADO) {
        return ERR_CLIENTE_NAO_ENCONTRADO;
    }

    Cliente *alvo = &b->clientes[indice];

    // 1. Busca
    for (int i = 0; i < b->quant_clientes; i++) {
        if (b->clientes[i].id == id_cliente) {
            alvo = &b->clientes[i];
            break;
        }
    }

    if (alvo == NULL) {
        printf("Erro: Cliente nao encontrado.\n");
        return -1;
    }

    // 2. Menu de Edição
    int opcao;
    do {
        printf("\n--- ALTERANDO: %s ---\n", alvo->nome);
        printf("1. Alterar Nome\n");
        printf("2. Alterar Digitos (Cartao Principal)\n");
        printf("3. Alterar Parceiro (Cartao Principal)\n");
        printf("4. Alterar Saldo (Cartao Principal)\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch(opcao) {
            case 1:
                printf("\nNovo Nome: ");
                fgets(alvo->nome, TAM_NOME, stdin);
                alvo->nome[strcspn(alvo->nome, "\n")] = 0;
                break;
            case 2:
                printf("\nNovos Digitos: ");
                fgets(alvo->cartoes[0].ultimos_digitos, TAM_DIGITOS, stdin);
                alvo->cartoes[0].ultimos_digitos[strcspn(alvo->cartoes[0].ultimos_digitos, "\n")] = 0;
                break;
            case 3:
                printf("\nNovo Parceiro: ");
                fgets(alvo->cartoes[0].nome_parceiro, TAM_PARCEIRO, stdin);
                alvo->cartoes[0].nome_parceiro[strcspn(alvo->cartoes[0].nome_parceiro, "\n")] = 0;
                break;
            case 4:
                printf("\nNovo Saldo: ");
                scanf("%lf", &alvo->cartoes[0].saldo);
                limpar_buffer();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida. Escolha uma opcao entre 0 e 4.\n");
        }
    } while (opcao != 0);

    return OK;
}

int buscar_indice_cliente(BancoDados *b, int id) {
    for (int i = 0; i < b->quant_clientes; i++) {
        if (b->clientes[i].id == id) {
            return i; // Achou! Retorna a posição dele
        }
    }
    return ERR_CLIENTE_NAO_ENCONTRADO; // Rodou tudo e não achou
}