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
                printf("\nDigite o nome do cliente:");
                fgets(NOME, TAM_NOME, stdin);
                NOME[strcspn(NOME, "\n")] = 0;

                tratar_retorno(adicionar_cliente(banco, NOME),
                    "Cliente cadastrado com sucesso",
                    "cadastrar cliente");
            }
            break;
            case 2: {
                printf("\n=== Clientes cadastrados (%d)===\n",
                    banco->quant_clientes);
                for (int i = 0; i < banco->quant_clientes; i++) {
                    printf("\nID: %d\t Nome: %s\t Cartoes: %d",
                        banco->clientes[i].id,
                        banco->clientes[i].nome,
                        banco->clientes[i].quant_cartoes);
                }
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