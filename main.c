#include <stdio.h>
#include <inttypes.h>
#include "arvoreB.h"

int main() {
    int32_t t = 3;

    // 🔹 Criar árvore
    arvoreB *arvore = criarArvoreB(t);

    if (arvore == NULL) {
        printf("Erro ao criar arvore\n");
        return 1;
    }

    printf("Arvore B criada com sucesso!\n");
    printf("Grau minimo (t): %d\n\n", arvore->t_arvore);

    // 🔹 Inserções (forçam splits)
    int valores[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 2, 1};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        printf("Inserindo %d...\n", valores[i]);
        inserirArvoreB(arvore, valores[i]);
    }

    // 🔹 Impressão em ordem
    imprimirEmOrdem(arvore);

    // 🔹 Teste de busca (mesmo que ainda não implementada)
    int32_t idx;
    int32_t chave_busca = 12;

    struct nodo* resultado = buscarArvoreB(arvore, chave_busca, &idx);

    if (resultado != NULL) {
        printf("\nChave %d encontrada no indice %d do nodo.\n", chave_busca, idx);
    } else {
        printf("\nChave %d NAO encontrada.\n", chave_busca);
    }

    // 🔹 Teste de busca de elemento inexistente
    chave_busca = 99;
    resultado = buscarArvoreB(arvore, chave_busca, &idx);

    if (resultado != NULL) {
        printf("Chave %d encontrada no indice %d do nodo.\n", chave_busca, idx);
    } else {
        printf("Chave %d NAO encontrada.\n", chave_busca);
    }

    // 🔹 Liberação de memória
    deletarArvore(arvore);
    printf("\nArvore deletada com sucesso!\n");

    return 0;
}