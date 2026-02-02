#include <stdio.h>
#include <stdlib.h>
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
    }while (opcao != 0);

    mostrar_menu();


    tratar_retorno(
        salvar_clientes(banco), "Cliente salvo",
        "salvar cliente"
        );

    return 0;
}