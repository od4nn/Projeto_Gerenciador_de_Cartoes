# 💳 Sistema de Gestão de Cartões (CLI)

Um sistema de gerenciamento de clientes e cartões desenvolvido inteiramente em **C**. Este projeto nasceu da necessidade de resolver um problema real: a desorganização no controle manual de cartões, parceiros e limites de crédito em pequenos negócios/uso pessoal.

Atualmente, o projeto é um **MVP (Produto Mínimo Viável)** executado via terminal (CLI - Command Line Interface), construído como aplicação prática dos conceitos de Algoritmos e Programação Estruturada vistos na faculdade.

## ✨ Funcionalidades

O sistema realiza um CRUD completo e lida com um **relacionamento 1:N** (Um Cliente para Muitos Cartões):

- **Cadastro de Clientes:** Criação de novos perfis já vinculados a um cartão inicial.
- **Adição de Cartões Extras:** Capacidade de vincular múltiplos cartões (de diferentes parceiros/bandeiras) a um único cliente existente.
- **Listagem e Relatórios:** Exibição hierárquica de todos os clientes e seus respectivos cartões e saldos.
- **Atualização de Dados:** Menu dedicado para alterar informações e atualizar saldos.
- **Persistência de Dados:** Salvamento automático das informações em disco (`.txt`), garantindo que nenhum dado seja perdido ao fechar o programa.

## 🛠️ Tecnologias e Conceitos Aplicados

Este não é apenas um script simples. O sistema foi desenhado aplicando conceitos pesados de Engenharia de Software e gerenciamento de memória:

* **Linguagem C:** Base sólida do projeto.
* **Alocação Dinâmica de Memória:** Uso de `malloc` e `realloc` para criar vetores dinâmicos de clientes e cartões, expandindo a memória sob demanda sem desperdício.
* **Ponteiros e Estruturas Aninhadas (Structs):** Manipulação de ponteiros de structs dentro de outras structs para criar o relacionamento Cliente -> Cartões.
* **Persistência / Serialização Customizada:** Lógica própria para transformar dados complexos da memória RAM (Pai e Filhos) em texto plano (HD) e reconstruir essa estrutura ao iniciar o programa.
* **Tratamento de Input e Buffer:** Prevenção de bugs de leitura de teclado (`stdin`) usando `fgets` e limpeza de buffer.

## 🚀 Como Executar

1. Clone este repositório:
   ```bash
   git clone [https://github.com/SEU_USUARIO/NOME_DO_REPOSITORIO.git](https://github.com/SEU_USUARIO/NOME_DO_REPOSITORIO.git)

2. Compile o código usando o GCC:
   ```bash
   gcc main.c dados.c -o gestao_cartoes

3. Execute o programa:
   ```bash
   ./gestao_cartoes

  ## 🔮 Próximos Passos (Roadmap)
  
  [ ] Implementar a exclusão de cartões e clientes (Delete).

  [ ] Criar função para liberação total de memória (free) ao encerrar o sistema.

  [ ] Evolução: Escalar a lógica de backend construída aqui para uma aplicação Web completa (Fullstack) no futuro.
