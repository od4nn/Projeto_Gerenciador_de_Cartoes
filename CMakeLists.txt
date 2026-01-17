cmake_minimum_required(VERSION 3.20)
project(Projeto_Cartoes_Distribuidora C)

set(CMAKE_C_STANDARD 11)

# Aqui dizemos: O executável final é feito a partir destes arquivos nessas pastas
add_executable(Projeto_Cartoes_Distribuidora
        Gerenciador-de-cartoes/main.c
        Gerenciador-de-cartoes/dados.h
        Gerenciador-de-cartoes/dados.c
        Gerenciador-de-cartoes/uteis.c
)