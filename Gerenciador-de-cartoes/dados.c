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

        // 1. Salva o CABEÇALHO do cliente (ID;Nome;Quantidade de Cartões)
        fprintf(f, "%d;%s;%d\n", c.id, c.nome, c.quant_cartoes);

        // 2. Loop para salvar TODOS os cartões dele logo abaixo
        for (int j = 0; j < c.quant_cartoes; j++) {
            fprintf(f, "%s;%s;%.2lf\n",
                c.cartoes[j].ultimos_digitos,
                c.cartoes[j].nome_parceiro,
                c.cartoes[j].saldo
            );
        }
    }
    // O marcador de fim ajuda a saber quando parar
    fprintf(f, "Fim da lista.\n");

    fclose(f);
    return OK;
}

int carregar_clientes(BancoDados *b) {
    FILE *f = fopen("dados_clientes.txt", "r");
    if (f == NULL) return OK;

    char linha[300];

    // Variáveis temporárias
    int id_lixo, qtd_cartoes_total;
    char nome_tmp[TAM_NOME];

    char digitos_tmp[TAM_DIGITOS];
    char parceiro_tmp[TAM_PARCEIRO];
    double saldo_tmp;

    // Loop principal: Tenta ler o CABEÇALHO do cliente
    while (fgets(linha, 300, f) != NULL) {
        // Se achou o fim da lista, para.
        if (strncmp(linha, "Fim da lista.", 13) == 0) break;

        linha[strcspn(linha, "\n")] = 0;

        // 1. Lê os dados do Cliente
        int status = sscanf(linha, "%d;%[^;];%d", &id_lixo, nome_tmp, &qtd_cartoes_total);

        if (status == 3) {
            // Se leu o cliente com sucesso, SABEMOS que a próxima linha é o 1º cartão.
            // Então forçamos a leitura da próxima linha agora:
            if (fgets(linha, 300, f) != NULL) {
                linha[strcspn(linha, "\n")] = 0;
                sscanf(linha, "%[^;];%[^;];%lf", digitos_tmp, parceiro_tmp, &saldo_tmp);

                // Cria o cliente com o 1º cartão
                adicionar_cliente(b, nome_tmp, digitos_tmp, parceiro_tmp, saldo_tmp);

                // Pegamos o ID do cliente que acabou de ser criado (é o último da lista)
                int id_novo_cliente = b->clientes[b->quant_clientes - 1].id;

                // 2. Se o arquivo diz que ele tinha MAIS cartões, vamos ler o resto
                // Começamos o k=1 porque o cartão 0 já foi lido acima
                for (int k = 1; k < qtd_cartoes_total; k++) {
                    fgets(linha, 300, f); // Lê a linha do cartão extra
                    linha[strcspn(linha, "\n")] = 0;

                    sscanf(linha, "%[^;];%[^;];%lf", digitos_tmp, parceiro_tmp, &saldo_tmp);

                    // Adiciona como extra
                    adicionar_cartao_extra(b, id_novo_cliente, digitos_tmp, parceiro_tmp, saldo_tmp);
                }
            }
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