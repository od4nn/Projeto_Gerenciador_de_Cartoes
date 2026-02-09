#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DADOS.H"

int main() {
    setbuf(stdout, NULL);

    BancoDados *banco = inicializar_banco();

    tratar_retorno(
        carregar_clientes(banco),
        "Dados recuperados do arquivo",
        "ao carregar backup");
    int opcao;
    do {
        mostrar_menu();
        scanf("%d", &opcao);

        limpar_buffer();

        switch (opcao) {
            case 1: {
                char NOME[TAM_NOME];
                char PARCEIRO[TAM_PARCEIRO];
                char DIGITOS[TAM_DIGITOS];
                double SALDO;

                printf("\nDigite o nome do cliente:");
                fgets(NOME, TAM_NOME, stdin);
                NOME[strcspn(NOME, "\n")] = 0;

                printf("Informe os ultimos 4 digitos do cartao: ");
                fgets(DIGITOS, TAM_DIGITOS, stdin);
                DIGITOS[strcspn(DIGITOS, "\n")] = 0;

                printf("Informe o nome da loja parceira: ");
                fgets(PARCEIRO, TAM_PARCEIRO, stdin);
                PARCEIRO[strcspn(PARCEIRO, "\n")] = 0;

                printf("Informe o saldo do cartao: ");
                scanf("%lf", &SALDO);
                limpar_buffer();

                tratar_retorno(adicionar_cliente(banco, NOME, DIGITOS, PARCEIRO, SALDO),
                    "Cliente e cartao inicial salvos!",
                    "cadastrar cliente");
            }
            break;
            case 2: {
                printf("\n=== Clientes cadastrados (%d)===\n",
                    banco->quant_clientes);
                for (int i = 0; i < banco->quant_clientes; i++) {
                    Cliente c = banco->clientes[i]; //atalho para facilitar leitura

                    printf("\nID: %d\t Nome: %s\t", c.id, c.nome);
                    printf("Cartao: %s\t Parceiro: %s\t Saldo: %lf\n",
                        c.cartoes[i].ultimos_digitos, c.cartoes[i].nome_parceiro,
                        c.cartoes[i].saldo);
                }
                printf("------------------------------------------");
            }
            break;
            case 0: {
                printf("\nEncerrando sistema...");
                break;
            }
            default:
                printf("\nErro: Opcao invalida! "
                       "Escolha uma opcao (0, 1 ou 2).");
        }
    }while (opcao != 0);
    tratar_retorno(salvar_clientes(banco), "Dados salvos com seguranca.",
        "salvar dados.");

    return OK;
}