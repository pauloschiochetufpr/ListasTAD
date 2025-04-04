#include  <stdio.h>
#include <stdlib.h>
#include "biblioencad.h"

int main() {
    Biblioteca b;

    inicializarBiblioteca(&b);

    cadastrarLivro(&b, "Capitaes da Areia", "Jorge Amado", 1937, "3333333333333");
    cadastrarLivro(&b, "Dom Casmurro", "Machado de Assis", 1899, "4444444444444");

    //Cadastrar e mostrar os 5000 livros usou 70% do CPU e 40% da memória do PC da faculdade
    for(int i=0;i<4998;i++){
        char titulo[MAX_TITULO];
        char isbn[MAX_ISBN];

        // Gerando o título como "livro1", "livro2", etc.
        snprintf(titulo, sizeof(titulo), "livro%d", i);

        // Gerando o ISBN como o número da iteração
        snprintf(isbn, sizeof(isbn), "%d", i);

        // Chama a função para cadastrar o livro
        // Aqui, você também precisa passar o autor e o ano. Vou usar valores fixos como exemplo
        if (cadastrarLivro(&b, titulo, "Autor Exemplo", 2020, isbn) == 0) {
            printf("Livro %d cadastrado com sucesso!\n", i);
        } else {
            printf("Erro ao cadastrar o livro %d.\n", i);
        }
    }

    listarTodosLivros(&b);

    emprestarLivro(&b, "3333333333333", "Joao", "04/04/2025");

    listarTodosLivros(&b);

    destruirBiblioteca(&b);

    return 0;

}