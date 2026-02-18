#ifndef DADOS_H
#define DADOS_H

//Definindo tamanhos para o projeto
#define TAM_NOME 100
#define TAM_DIGITOS 10 //so usaremos 6 mas enfim
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
    ERR_FALTA_MEMORIA = 1, // Falha malloc/realloc
    ERR_LEITURA = 2, //Falha ao salvar dados dos clientes
    ERR_CLIENTE_NAO_ENCONTRADO = 3,
}CodigosErro;

    /*===Prototipos===*/

BancoDados* inicializar_banco();

int adicionar_cliente(BancoDados *b, char *nome, char *digitos,
    char *parceiro, double saldo);

void tratar_retorno (int codigo, char *msg_sucesso, char *msg_erro);

int salvar_clientes(BancoDados *b);

void mostrar_menu ();

int carregar_clientes (BancoDados *b);

void limpar_buffer();

int adicionar_cartao_extra(BancoDados *b, int id_cliente, char *digitos,
    char *parceiro, double saldo);

int alterar_dados_cliente(BancoDados *b, int id_cliente);
#endif