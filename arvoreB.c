#include <stdio.h>
#include <inttypes.h>
#include "arvoreB.h"
#include <stdlib.h>
struct arvoreB* criarArvoreB(int32_t t_arvore){
    //Gabriel: podemos assumir que a entrada vai ser um int mesmo? No main do professor vai ter validação? 
    if(t_arvore <= 0){
        printf("Valor de tamanho invalido.");
        return NULL;
    }    

    struct arvoreB *novo = (arvoreB*) malloc(sizeof(arvoreB));
    if(!novo){
        fprintf(stderr, "Falha ao alocar memoria.\n");
        exit(1);
    }
    novo->t_arvore = t_arvore;
    novo->raiz = NULL;

    return novo;
}


//Aloca uma struct do tipo arvoreB com um valor de T específico e a retorna.

void inserirArvoreB(struct arvoreB* arvore, int32_t chave){

}
//Insere a chave na Árvore B.

void imprimirArvoreB(struct arvoreB* arvore);

/*Imprime a Árvore B na tela em largura, seguindo estritamente o padrão do exemplo (não
seguir o padrão invalidará sua função).
No exemplo, ao imprimir a lista de nodos do nível, faça no formato F/I (n:NUMEROCHAVES)
[chave0<espaço>chave1<espaço>...]<espaço><espaço>PROXIMONODO onde F/I indica
se o nodo é uma Folha ou um nodo Interno
----//----
Nivel 0
----//----
I (n:1) [4]
----//----
Nivel 1
----//----
I (n:1) [2] I (n:3) [6 8 10]
----//----
Nivel 2
----//----
F (n:1) [1] F (n:1) [3] F (n:1) [5] F (n:1) [7] F (n:1) [9] F (n:2) [11 12]*/
void imprimirNo(struct nodo *no){
    if(no == NULL){
        return;
    }

    int i =0;
    while(i < no->numero_chaves){
        imprimirNo(no->filhos[i]);
        printf("%d ", no->chaves[i]);
        i++;
    }

    imprimirNo(no->filhos[i]); 
    return;
}

void imprimirEmOrdem(struct arvoreB* arvore){
    if (arvore == NULL || arvore->raiz == NULL) {
        return;
    }
    printf("\nEm ordem: ");
    imprimirNo(arvore->raiz);
    printf("\n");
    return;
}
/*Imprime as chaves da árvore em ordem, seguindo o formato exemplificado a seguir:
Em ordem: 1 2 3 4 5 6 7 8 9 10 11 12*/

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,int32_t* idxEncontrado){

}
/*union ou struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,int32_t* idxEncontrado);*/
/*Retorna o endereço do nodo que contém a chave sendo buscada, e insere o índice onde essa
chave se encontra dentro de idxEncontrado. Caso não encontre a chave, retorna NULL e
insere -1 em idxEncontrado.*/
void apaga_valores_nodo(struct nodo *no){
        free(no->chaves);
        free(no->filhos);
        free(no);
        return;
}

void libera_nodos(struct nodo *no){

    if(no == NULL){
        return;
    }
    
    
    for(int i=0;i <= no->numero_chaves;i++){
        libera_nodos(no->filhos[i]);
    }
    apaga_valores_nodo(no);
    return;
}

void deletarArvore(struct arvoreB* arvore){
    if(arvore == NULL){
        return;
    }
    
    libera_nodos(arvore->raiz);
    free(arvore);    
    
    return;
};
/*Libera toda a memória alocada. Ou seja, todos os nodos são liberados, além da struct
arvoreB passada como parâmetro.*/