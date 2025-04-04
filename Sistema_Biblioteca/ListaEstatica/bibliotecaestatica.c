#include "bibliotecaestatica.h"
#include <string.h>
#include <stdio.h>


void inicializarBiblioteca(Biblioteca* b) {
b->totalLivros = 0;
}


// Implemente a função de cadastro: verificar se há espaço, preencher os dados e adicionar ao vetor
int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {

    if (b->totalLivros >= MAX_LIVROS) {
        printf("Erro: Não há espaço para mais livros na biblioteca.\n");
        return 0;
    }


    if (strlen(titulo) == 0 || strlen(autor) == 0) {
        printf("Erro: Título e autor não podem ser vazios!\n");
        return 0;
    }

 
    if (strlen(isbn) != 13) {
        printf("Erro: ISBN inválido! O ISBN deve ter 13 caracteres.\n");
        return 0;
    }

    Livro* novo = &b->livros[b->totalLivros];
    strncpy(novo->titulo, titulo, MAX_TITULO - 1);
    novo->titulo[MAX_TITULO - 1] = '\0';  

    strncpy(novo->autor, autor, MAX_AUTOR - 1);
    novo->autor[MAX_AUTOR - 1] = '\0';  

    novo->ano = ano;
    
    strncpy(novo->isbn, isbn, MAX_ISBN - 1);
    novo->isbn[MAX_ISBN - 1] = '\0';  

    novo->status = DISPONIVEL;
    novo->usuario[0] = '\0';  
    novo->dataEmprestimo[0] = '\0';  

    b->totalLivros++;

    return 1;  
}

void listarTodosLivros(Biblioteca* b) {

for (int i = 0; i < b->totalLivros; i++) {

printf("%s - %s - %d - %s\n", b->livros[i].titulo, b->livros[i].autor, b->livros[i].ano, b->livros[i].isbn);
    }

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

int alterarStatus (Biblioteca* b, char* isbn, int novoStatus){
    Livro* livro = consultarLivroPorISBN(b, isbn);
    if (livro =! NULL) {
        livro->status = novoStatus;
        return 1;
    }
    return 0;
}
