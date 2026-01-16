
#ifndef DADOS_H
#define DADOS_H

//Definindo tamanhos para o projeto
#define TAM_NOME 100
#define TAM_DIGITOS 5
#define TAM_PARCEIRO 50

    /*===Structs===*/

//Cartao
typedef struct {
    int id;
    char ultimos_digitos[TAM_DIGITOS];
    char nome_parceiro[TAM_PARCEIRO];
    double saldo;
}Cartao;

//Cliente (Dono do cartao)
typedef struct {
    int id;
    char nome[TAM_NOME];
    Cartao *cartoes;
    int quant_cartoes;
    int capacidade_cartoes;
}Cliente;

//Banco de dados
typedef struct {
    //vetor dinamico
    Cliente *clientes;
    int quant_clientes;
    int capacidade_clientes;
}BancoDados;

    /*===Enum para Erros===*/
typedef enum {
    OK = 0, //Sucesso geral

    //ERROS:
    ERR_FALTA_MEMORIA = 1 // Falha malloc/realloc
}CodigosErro;

    /*===Prototipos===*/

BancoDados* inicializar_banco();

void adicionar_cliente(BancoDados *b, char *nome);

#endif