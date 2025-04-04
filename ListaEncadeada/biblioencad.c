#include "biblioencad.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void inicializarBiblioteca(Biblioteca* b) {
    b->primeiro = NULL;
    b->totalLivros = 0;
}


int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    // Verificar se ISBN já existe
    NoLivro* livroExistente = consultarLivroPorISBN(b, isbn);
    if (livroExistente != NULL) {
        printf("Erro: ISBN ja existe na biblioteca.\n");
        return -1; // ISBN duplicado
    }

    // Criar novo nó e preencher dados
    if(b == NULL) return 0;
    NoLivro* novoLivro = (NoLivro*)malloc(sizeof(NoLivro));

    strncpy(novoLivro->livro.titulo, titulo, MAX_TITULO);
    strncpy(novoLivro->livro.autor, autor, MAX_AUTOR);
    novoLivro->livro.ano = ano;
    strncpy(novoLivro->livro.isbn, isbn, MAX_ISBN);
    novoLivro->livro.status = DISPONIVEL;
    novoLivro->livro.usuario[0] = '\0';  // Nenhum usuário no momento
    novoLivro->livro.dataEmprestimo[0] = '\0'; // Nenhuma data no momento

    // Inserir no início da lista
    novoLivro->proximo = b->primeiro;
    b->primeiro = novoLivro;

    // Atualizar contador de livros
    b->totalLivros++;

    printf("Livro cadastrado com sucesso: %s\n", titulo);
    return 0; // Sucesso

}


void listarTodosLivros(Biblioteca* b) {

    // Percorrer a lista com um ponteiro e imprimir dados
    if (b->primeiro == NULL) {
        printf("A biblioteca esta vazia.\n");
        return;
    }

    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        printf("Titulo: %s\n", atual->livro.titulo);
        printf("Autor: %s\n", atual->livro.autor);
        printf("Ano: %d\n", atual->livro.ano);
        printf("ISBN: %s\n", atual->livro.isbn);
        printf("Status: %s\n", (atual->livro.status == DISPONIVEL) ? "Disponível" : "Emprestado");
        if (atual->livro.status == EMPRESTADO) {
            printf("Usuario: %s\n", atual->livro.usuario);
            printf("Data do Emprestimo: %s\n", atual->livro.dataEmprestimo);
        }
        printf("\n");
        atual = atual->proximo;
    }

}


int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {

    // Percorrer lista e alterar status se encontrar
    NoLivro* livro = consultarLivroPorISBN(b, isbn);
    if (livro == NULL) {
        printf("Erro: Livro nao encontrado.\n");
        return -1; // Livro não encontrado
    }

    if (livro->livro.status == EMPRESTADO) {
        printf("Erro: Livro ja esta emprestado.\n");
        return -1; // Livro já emprestado
    }

    // Atualizar status para EMPRESTADO
    livro->livro.status = EMPRESTADO;
    strncpy(livro->livro.usuario, usuario, MAX_USUARIO);
    strncpy(livro->livro.dataEmprestimo, data, MAX_DATA);

    printf("Livro emprestado com sucesso a %s na data %s.\n", usuario, data);
    return 0; // Sucesso

}


int devolverLivro(Biblioteca* b, char* isbn) {

    // Percorrer lista e alterar status
    NoLivro* livro = consultarLivroPorISBN(b, isbn);
    if (livro == NULL) {
        printf("Erro: Livro nao encontrado.\n");
        return -1; // Livro não encontrado
    }

    if (livro->livro.status == DISPONIVEL) {
        printf("Erro: O livro ja esta disponível.\n");
        return -1; // O livro já está disponível
    }
    
     // Atualizar status para DISPONIVEL
     livro->livro.status = DISPONIVEL;
     livro->livro.usuario[0] = '\0';  // Limpar usuário
     livro->livro.dataEmprestimo[0] = '\0'; // Limpar data
 
     printf("Livro devolvido com sucesso.\n");
     return 0; // Sucesso

}

NoLivro* consultarLivroPorISBN(Biblioteca* b, char* isbn) {

    // Buscar nó com ISBN correspondente
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strncmp(atual->livro.isbn, isbn, MAX_ISBN) == 0) {
            return atual; // Livro encontrado
        }
        atual = atual->proximo;
    }
    return NULL; // Livro não encontrado

}


void destruirBiblioteca(Biblioteca* b) {

    // Liberar todos os nós da lista com free
    NoLivro* atual = b->primeiro;
    NoLivro* temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp); // Liberar o nó
    }
    b->primeiro = NULL; // Garantir que a lista está vazia
    b->totalLivros = 0;  // Zerando o contador de livros
    free(b);
    printf("Biblioteca destruida com sucesso.\n");

}