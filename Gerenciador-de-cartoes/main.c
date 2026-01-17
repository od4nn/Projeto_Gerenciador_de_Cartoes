#include <stdio.h>
#include <stdlib.h>
#include "DADOS.H"

int main() {
    setbuf(stdout, NULL);
    BancoDados *banco = inicializar_banco();

     tratar_retorno(
         adicionar_cliente(banco, "Maria Jose"),
         "Cliente cadastrado(a)", "cadastrar cliente"
         );

     printf("\nCliente numero 1: %s\n", banco->clientes[0].nome);

    return 0;
}