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
                printf("\n=== Clientes cadastrados (%d)===\n", banco->quant_clientes);

                for (int i = 0; i < banco->quant_clientes; i++) {
                    Cliente c = banco->clientes[i];

                    printf("ID: %d | Nome: %s (Total Cartoes: %d)\n", c.id, c.nome, c.quant_cartoes);

                    // Loop J para percorrer OS CARTÕES deste cliente específico
                    for(int j = 0; j < c.quant_cartoes; j++) {
                        printf("   -> Cartao %d: %s [%s] - Saldo: R$ %.2f\n",
                            j+1,
                            c.cartoes[j].nome_parceiro,
                            c.cartoes[j].ultimos_digitos,
                            c.cartoes[j].saldo
                        );
                    }
                    printf("------------------------------------------\n");
                }
            }
                break;

            case 3: {
                int id_busca;

                printf("\n--- NOVO CARTAO EXTRA ---\n");
                printf("Informe o ID do Cliente: ");
                scanf("%d", &id_busca);
                limpar_buffer();

                // AQUI ESTÁ A MÁGICA:
                // Verificamos antes de continuar
                if (buscar_indice_cliente(banco, id_busca) == ERR_CLIENTE_NAO_ENCONTRADO) {
                    printf("\nErro: Cliente com ID %d nao existe!\n", id_busca);
                    printf("Operacao cancelada.\n");
                    break; // Sai do case e volta pro menu
                }

                // Se chegou aqui, é porque o cliente existe!
                char DIGITOS[TAM_DIGITOS];
                char PARCEIRO[TAM_PARCEIRO];
                double SALDO;

                printf("\nCliente encontrado! Prossiga com os dados do novo cartao.\n");

                printf("Digitos: ");
                fgets(DIGITOS, TAM_DIGITOS, stdin);
                DIGITOS[strcspn(DIGITOS, "\n")] = 0;

                printf("Parceiro: ");
                fgets(PARCEIRO, TAM_PARCEIRO, stdin);
                PARCEIRO[strcspn(PARCEIRO, "\n")] = 0;

                printf("Saldo: ");
                scanf("%lf", &SALDO);

                tratar_retorno(
                    adicionar_cartao_extra(banco, id_busca, DIGITOS,
                        PARCEIRO, SALDO),
                    "Cartao vinculado!",
                    "vincular cartao"
                );
                break;
            }

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