#include "biblioteca_estatica.h"
#include <string.h>
#include <stdio.h>

void inicializarBiblioteca(Biblioteca* b) {
    b->totalLivros = 0;
}

int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    if (b->totalLivros >= MAX_LIVROS) return 0;

    Livro* novo = &b->livros[b->totalLivros];
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    novo->ano = ano;
    strcpy(novo->isbn, isbn);
    novo->status = DISPONIVEL;
    novo->usuario[0] = '\0';
    novo->dataEmprestimo[0] = '\0';

    b->totalLivros++;
    return 1;
}

void listarTodosLivros(Biblioteca* b) {
    printf("Lista de Livros\n");
    for (int i = 0; i < b->totalLivros; i++) {
        Livro l = b->livros[i];
        printf("%s | %s | %d | %s | %s\n", 
               l.titulo, l.autor, l.ano, l.isbn,
               l.status == DISPONIVEL ? "Disponível" : "Emprestado");
        if (l.status == EMPRESTADO) {
            printf("Emprestado para: %s em %s\n", l.usuario, l.dataEmprestimo);
        }
    }
    printf("===========================\n\n");
}

int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == DISPONIVEL) {
            b->livros[i].status = EMPRESTADO;
            strcpy(b->livros[i].usuario, usuario);
            strcpy(b->livros[i].dataEmprestimo, data);
            return 1;
        }
    }
    return 0;
}

int devolverLivro(Biblioteca* b, char* isbn) {
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == EMPRESTADO) {
            b->livros[i].status = DISPONIVEL;
            b->livros[i].usuario[0] = '\0';
            b->livros[i].dataEmprestimo[0] = '\0';
            return 1;
        }
    }
    return 0;
}

Livro* consultarLivroPorISBN(Biblioteca* b, char* isbn) {
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0) {
            return &b->livros[i];
        }
    }
    return NULL;
}
