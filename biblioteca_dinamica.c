#include "biblioteca_dinamica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INICIAL 10

//inicia a lista encadeada dinamicamente
void inicializarBiblioteca(Biblioteca* b) {

    b->livros = (Livro*) malloc(INICIAL * sizeof(Livro));
    b->capacidade = INICIAL; // capacidade inicial
    b->totalLivros = 0;

}

// Esta função realoca o vetor de livros com nova capacidade
void redimensionarBiblioteca(Biblioteca* b, int novaCapacidade) {
// Completar: usar realloc para redimensionar e atualizar b->capacidade
    if (b->totalLivros == b->capacidade){
        b->capacidade = novaCapacidade;
        b->livros = (Livro*) realloc(b->livros, b->capacidade * sizeof(Livro));
    }

    if (b->livros == NULL) {
        printf("Erro ao realocar memória\n");
    }
}

// Cadastrar livro (com verificação de ISBN e redimensionamento automático)

int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    
    if (b->totalLivros == b->capacidade){
        redimensionarBiblioteca(b, b->capacidade * 2);
    }
    // Verifica se ISBN já existe
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0) {
            printf("ISBN já existente.\n");
            return 0;
        }
    }
    
    Livro novoLivro;

    strcpy(novoLivro.titulo, titulo);
    strcpy(novoLivro.autor, autor);
    novoLivro.ano = ano;
    strcpy(novoLivro.isbn, isbn);
    novoLivro.usuario[0] = '\0';
    novoLivro.dataEmprestimo[0] = '\0';
    b->livros[b->totalLivros] = novoLivro;
    b->totalLivros = b->totalLivros + 1;
    return 1;
}

// Listar todos os livros
void listarTodosLivros(Biblioteca* b) {
    for (int i = 0; i < b->totalLivros; i++) {
        printf("Livro: %s | Ano: %d | Autor: %s | ISBN: %s | Status: %s | Usuario: %s | Data Emprestimo: %s\n",
            b->livros[i].titulo,
            b->livros[i].ano,
            b->livros[i].autor,
            b->livros[i].isbn,
            b->livros[i].status == EMPRESTADO ? "Emprestado" : "Disponivel",
            b->livros[i].usuario,
            b->livros[i].dataEmprestimo
        );
        printf("\n");
    }
}


// Emprestar livro
int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0) { 
            b->livros[i].status = EMPRESTADO;
            strcpy(b->livros[i].usuario, usuario);
            strcpy(b->livros[i].dataEmprestimo, data);
            return 1; 
        }
    }
    return 0;
}


// Devolver livro
int devolverLivro(Biblioteca* b, char* isbn) {
// Completar: buscar pelo ISBN e alterar status
for (int i = 0; i < b->totalLivros; i++) {
    if (strcmp(b->livros[i].isbn, isbn) == 0) { 
        b->livros[i].status = DISPONIVEL;
        strcpy(b->livros[i].usuario, " ");
        strcpy(b->livros[i].dataEmprestimo, " ");
        return 1; 
    }
}
return 0;
}


// Buscar livro pelo ISBN

Livro* consultarLivroPorISBN(Biblioteca* b, char* isbn) {
// Completar: percorrer o vetor e comparar com strcmp
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0) { 
            printf("Livro: %s | Ano: %d | Autor: %s | ISBN: %s | Status: %s | Usuario: %s | Data Emprestimo: %s\n",
                b->livros[i].titulo,
                b->livros[i].ano,
                b->livros[i].autor,
                b->livros[i].isbn,
                b->livros[i].status == EMPRESTADO ? "Emprestado" : "Disponivel",
                b->livros[i].usuario,
                b->livros[i].dataEmprestimo
            );
            printf("\n");
        }
    }
}

// Liberar memória

void destruirBiblioteca(Biblioteca* b) {

free(b->livros);

b->livros = NULL;

b->capacidade = 0;

b->totalLivros = 0;

}