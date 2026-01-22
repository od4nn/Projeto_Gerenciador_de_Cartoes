#include <stdio.h>
#include <stdlib.h>
#include "DADOS.H"

int main() {
    setbuf(stdout, NULL);
    BancoDados *banco = inicializar_banco();

     //Carregando dados
     tratar_retorno(carregar_clientes(banco), "Dados carregados no arquivo.",
        "carregar dados antigos");

     tratar_retorno(
         adicionar_cliente(banco, "Ricardo Prime"),
         "Cliente cadastrado(a)", "cadastrar cliente"
         );

    tratar_retorno(
        adicionar_cliente(banco, "Joao Pedro"),
        "Cliente cadastrado(a)", "cadastrar cliente"
        );

    printf("\t\n---LISTA DE CLIENTES--- [TOTAL: %d]\n",
        banco->quant_clientes);
    for (int i = 0; i < banco->quant_clientes; i++) {
        printf("\nID %d: %s", banco->clientes[i].id, banco->clientes[i].nome);
    }
    printf("\n------------------------------------------------");


    //Salvar clientes
    tratar_retorno(
        salvar_clientes(banco), "Cliente salvo",
        "salvar cliente"
        );

    return OK;
}