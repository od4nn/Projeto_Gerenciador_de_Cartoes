#include <stdio.h>
#include <stdlib.h>
#include "DADOS.H"

int main() {
    BancoDados *banco = inicializar_banco();

     adicionar_cliente(banco, "Maria Jose");
     adicionar_cliente(banco, "Joao Pedro");
     printf("\nCliente numero 2: %s", banco->clientes[1].nome);

    return 0;
}