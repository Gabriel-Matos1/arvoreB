#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdint.h>
#include <stdbool.h>
#include "fila.h"

typedef struct nodo{
    bool folha;
    int32_t numero_chaves;
    int32_t *chaves;
    struct nodo **filhos;
} nodo;

typedef struct arvoreB {
    int32_t t_arvore;
    struct nodo* raiz;
} arvoreB;

struct arvoreB* criarArvoreB(int32_t t_arvore);
//Aloca uma struct do tipo arvoreB com um valor de T específico e a retorna.

void inserirArvoreB(struct arvoreB* arvore, int32_t chave);
//Insere a chave na Árvore B.

void imprimirArvoreB(struct arvoreB* arvore);
/*Imprime a Árvore B na tela em largura */

void imprimirEmOrdem(struct arvoreB* arvore);
/*Imprime as chaves da árvore em ordem, seguindo o formato exemplificado a seguir:
Em ordem: 1 2 3 4 5 6 7 8 9 10 11 12*/

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado);
/*Retorna o endereço do nodo que contém a chave sendo buscada, e insere o índice onde essa
chave se encontra dentro de idxEncontrado. Caso não encontre a chave, retorna NULL e
insere -1 em idxEncontrado.*/
void deletarArvore(struct arvoreB* arvore);

/*Libera toda a memória alocada. Ou seja, todos os nodos são liberados, além da struct
arvoreB passada como parâmetro.*/
#endif