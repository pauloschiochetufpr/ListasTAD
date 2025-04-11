#include <stdio.h>
#include "biblioteca_dinamica.h"


int main() {

Biblioteca b;
inicializarBiblioteca(&b);
cadastrarLivro(&b, "A Metamorfose", "Kafka", 1915, "1111111111111");
cadastrarLivro(&b, "O Pequeno Príncipe", "Saint-Exupéry", 1943, "2222222222222");
for(int i=0;i<4998;i++){
    char titulo[MAX_TITULO];
    char isbn[MAX_ISBN];
    // Código do thiago reaplicado aqui para fazer os 5000 livros.
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
emprestarLivro(&b, "1111111111111", "Ana", "04/04/2025");
listarTodosLivros(&b);
devolverLivro(&b, "1111111111111");
listarTodosLivros(&b);
consultarLivroPorISBN(&b, "2222222222222");
destruirBiblioteca(&b);

return 0;

}