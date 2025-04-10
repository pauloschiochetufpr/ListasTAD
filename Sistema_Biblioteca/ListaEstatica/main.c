#include <stdio.h>
#include "biblioteca_estatica.h"

int main() {
    Biblioteca b;
    inicializarBiblioteca(&b);

    cadastrarLivro(&b, "Dom Quixote", "Cervantes", 1605, "9876543210123");
    cadastrarLivro(&b, "1984", "George Orwell", 1949, "11111111111111");

    listarTodosLivros(&b);

    emprestarLivro(&b, "9876543210123", "Maria", "01/04/2025");

    listarTodosLivros(&b);

    Livro* livroConsultado = consultarLivroPorISBN(&b, "11111111111111");
    if (livroConsultado != NULL) {
        printf("Consulta: Livro encontrado - %s (%s)\n", livroConsultado->titulo,
               livroConsultado->status == DISPONIVEL ? "Disponível" : "Emprestado");
    } else {
        printf("Consulta: Livro não encontrado.\n");
    }

    if (devolverLivro(&b, "9876543210123")) {
        printf("Livro devolvido!\n");
    } else {
        printf("Erro.\n");
    }

    listarTodosLivros(&b);

    return 0;
}
