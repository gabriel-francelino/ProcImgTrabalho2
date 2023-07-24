# Esteganografia

Este projeto consiste no trabalho 2 da disciplina de Processamento de Imagens. 

## Objetivo

Decodificar um arquivo escondido nas imagens .PPM usando as técnicas de esteganografia.

[Descrição completa do trabalho](descricao_trabalho2.pdf)

## Requisitos
 - Linux ou WLS
 - gcc e make instalados

## Como executar

Este programa é executado por linha de comando e é passado como parâmetro o nome do arquivo esteganografado sem a extensao <.PPM>  

### 1) Compile o programa

```
    make
```

### 2) Execute o comando ./decode para decodificar a imagem

```
    ./decode <nome_arquivo_imagem>
```