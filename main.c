
#include <stdio.h>
#include "arvoreB.h"

int main() {
    int32_t t = 3;

    arvoreB *arvore = criarArvoreB(t);

    if (arvore == NULL) {
        printf("Erro ao criar arvore\n");
        return 1;
    }

    printf("Arvore B criada com sucesso!\n");
    printf("Grau minimo (t): %d\n", arvore->t_arvore);

    if (arvore->raiz == NULL) {
        printf("A arvore está vazia (raiz = NULL)\n");
    }

    return 0;
}