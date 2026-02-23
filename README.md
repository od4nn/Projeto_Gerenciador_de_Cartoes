# Sistema de Gestão de Cartões (CLI)

Um sistema de gerenciamento de clientes e cartões construído inteiramente em C. Desenvolvi este projeto para resolver um problema real: a bagunça no controle manual de cartões, parceiros e limites de crédito no dia a dia.

Atualmente, o projeto é um MVP rodando direto no terminal (CLI), criado para colocar em prática os conceitos de Algoritmos e Programação Estruturada vistos na faculdade.

## Funcionalidades

O sistema realiza um CRUD completo lidando com um relacionamento 1:N (um cliente pode ter vários cartões):

- Cadastro de Clientes: Cria o perfil já vinculando o primeiro cartão.
- Cartões Extras: Permite adicionar múltiplos cartões (de diferentes parceiros/bandeiras) a um cliente que já existe.
- Listagem e Relatórios: Exibe de forma hierárquica todos os clientes, seus cartões e saldos.
- Atualização de Dados: Menu para editar informações e atualizar o saldo.
- Persistência de Dados: Salva as informações automaticamente em disco (.txt), garantindo que os dados não sejam perdidos ao fechar o programa.

## Tecnologias e Conceitos Aplicados

O foco do projeto foi lidar com o gerenciamento manual da memória e estruturação de dados em C:

- Linguagem C: Base do projeto.
- Alocação Dinâmica de Memória: Uso de malloc e realloc para vetores dinâmicos, expandindo a capacidade do sistema sob demanda sem desperdiçar memória.
- Ponteiros e Structs Aninhadas: Uso de ponteiros de structs dentro de outras structs para criar a relação Cliente -> Cartões.
- Persistência / Serialização: Lógica própria para transformar os dados da memória RAM em texto plano (arquivo) e reconstruir essa estrutura ao reiniciar.
- Tratamento de Input e Buffer: Prevenção de bugs na leitura de teclado (stdin) usando fgets e rotinas de limpeza de buffer.

## Como Executar
```
1. Clone este repositório:
git clone https://github.com/od4nn/Projeto_Gerenciador_de_Cartoes.git

2. Entre na pasta onde estão os arquivos de código:
cd Projeto_Gerenciador_de_Cartoes/Gerenciador-de-cartoes

3. Compile o código usando o GCC (juntando todos os arquivos .c):
gcc main.c dados.c uteis.c -o gestao_cartoes

4. Execute o programa:
./gestao_cartoes

