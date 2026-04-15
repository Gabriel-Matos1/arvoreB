/*
ALUNOS: GABRIEL MATOS (GRR20240011), LEONARDO PIRES (GRR20232376)
DISCIPLINA DE ALGORITMOS 3 
PROVA PRÁTICA 1 
ABRIL DE 2026
*/
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "arvoreB.h"

struct arvoreB* criarArvoreB(int32_t t_arvore){
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

/*Aloca uma struct do tipo arvoreB com um valor de T específico e a retorna.*/
struct nodo* alocarNodo(struct arvoreB * arvore){
    struct nodo* novo = (nodo*) malloc(sizeof(nodo));
    if(!novo){
        fprintf(stderr,"Falha ao alocar memória.\n");
        exit(1);
    }

    int tamanho_t =2*arvore->t_arvore;
    novo->chaves = (int32_t*) malloc(sizeof(int32_t) * ((tamanho_t)-1));
    if(!novo->chaves){
        fprintf(stderr,"Falha ao alocar memória.\n");
        exit(1);
    }
    novo->filhos = malloc(sizeof(*novo->filhos) * tamanho_t);
    if(!novo->filhos){
        fprintf(stderr,"Falha ao alocar memória.\n");
        exit(1);
    }

    for(int i=0; i<tamanho_t; i++){
        novo->filhos[i] = NULL;
    }
    novo->numero_chaves = 0;
    novo->folha = true; 
    return novo;
}

void dividirFilho(struct nodo *nodo, int i, arvoreB *arvore){
    struct nodo* novo = nodo->filhos[i];
    struct nodo* auxiliar = alocarNodo(arvore);
    int t= arvore->t_arvore;    

    
    auxiliar->folha = novo->folha;
    auxiliar->numero_chaves = t-1; 
    
    for(int j=0; j<(t-1); j++){
        auxiliar->chaves[j] = novo->chaves[j+t];

    }
    if(!novo->folha){
        for(int j=0; j< t; j++){
            auxiliar->filhos[j] = novo->filhos[j+t];
        }
    }
    
    novo->numero_chaves = t-1;
    
    for(int q = (nodo->numero_chaves+1); q>(i+1); q--){
        nodo->filhos[q] = nodo->filhos[q-1];
    }
    
    nodo->filhos[i+1] = auxiliar;

    for(int q = (nodo->numero_chaves); q>(i); q--){
        nodo->chaves[q] = nodo->chaves[q-1];
    }

    nodo->chaves[i] = novo->chaves[t-1];
    nodo->numero_chaves = nodo->numero_chaves+1;

    
    return;
}


void inserirNaoCheio(struct nodo *nodo, int32_t chave, arvoreB * arvore){
    int num = nodo->numero_chaves-1;

    if(nodo->folha){
        while(num>=0 && chave < nodo->chaves[num]){
            nodo->chaves[num+1] = nodo->chaves[num];
            num--;
        }
        nodo->chaves[num+1] = chave;
        nodo->numero_chaves++;
        return;
    }else{
        while(num>=0 && chave < nodo->chaves[num]){
            num--;
        }
        num++;
        if(nodo->filhos[num]->numero_chaves == (2*arvore->t_arvore - 1)){
            dividirFilho(nodo, num, arvore);
            if(chave > nodo->chaves[num]){
                num++;
            }
        }
        inserirNaoCheio(nodo->filhos[num], chave, arvore);
    }
}

struct nodo* dividirRaiz(struct arvoreB* arvore){
    struct nodo * nova = alocarNodo(arvore);
    nova->folha = false;
    nova->numero_chaves = 0;
    nova->filhos[0] = arvore->raiz;
    arvore->raiz= nova;
    dividirFilho(nova, 0, arvore);
    
    return nova;
}

/*Insere a chave na Árvore B.*/
void inserirArvoreB(struct arvoreB* arvore, int32_t chave){
    if(arvore->raiz == NULL){
        struct nodo* raiz = alocarNodo(arvore);
        raiz->chaves[0] = chave;
        raiz->numero_chaves = 1;
        arvore->raiz = raiz;
        return;
    }


    struct nodo* r = arvore->raiz;

    if(r->numero_chaves == ((2*arvore->t_arvore)-1)){
        struct nodo * s = dividirRaiz(arvore);
        inserirNaoCheio(s, chave, arvore);    
    }   else{
        inserirNaoCheio(r, chave,arvore);
    }
    return;
}

/* imprime em largura com auxilio de fila */
void imprimirArvoreB(struct arvoreB* arvore){
    if (arvore->raiz == NULL)
        return;

    struct fila *f = fila_cria();
    if(f == NULL){
        fprintf(stderr,"Falha ao criar fila.\n");
        exit(1);
    }

    enqueue(f, arvore->raiz);
    int nivel = 0;
    char tipo;

    while (!fila_vazia(f)) {
        int tamanho = fila_tamanho(f);
        printf("\n----//----\n");
        printf("Nivel %d\n", nivel);
        printf("----//----\n");

        for (int i = 0; i < tamanho; i++) {
            struct nodo *atual;
            dequeue(f, &atual);

            if(atual->folha == 0){
                tipo = 'I';
            }
            else{
                tipo = 'F';
            }
                
            printf("%c (n:%d) ", tipo, atual->numero_chaves);
            for(int j = 0; j < atual->numero_chaves; j++){
                printf("[%d] ", atual->chaves[j]);
            }
            printf(" ");

            if(!atual->folha){
                for (int k = 0; k <= atual->numero_chaves; k++){
                    enqueue(f, atual->filhos[k]);
                }
            }
        }

        nivel++;
    }


    fila_destroi(&f);

    return;
}

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

/*Imprime as chaves da árvore em ordem crescente*/
void imprimirEmOrdem(struct arvoreB* arvore){
    if (arvore == NULL || arvore->raiz == NULL) {
        return;
    }
    printf("\nEm ordem: ");
    imprimirNo(arvore->raiz);
    printf("\n");
    return;
}

struct nodo* buscaAuxiliar(struct nodo* inicial, int32_t chave, int32_t* idxEncontrado){
    int i = 0;
    while(i < inicial->numero_chaves && chave > inicial->chaves[i]){
        i++;
    }

    if(i < inicial->numero_chaves && chave == inicial->chaves[i]){
        *idxEncontrado = i;
        
        return inicial;
    }
    else{
        if(inicial->folha == 1){
            *idxEncontrado = -1;

            return NULL;
        }
    }

    return buscaAuxiliar(inicial->filhos[i], chave, idxEncontrado);
}

/*Retorna o endereço do nodo que contém a chave sendo buscada, e insere o índice onde essa
chave se encontra dentro de idxEncontrado. Caso não encontre a chave, retorna NULL e
insere -1 em idxEncontrado.*/
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado){
    if (arvore->raiz == NULL){
        *idxEncontrado = -1;

        return NULL;
    }

    return (buscaAuxiliar(arvore->raiz, chave, idxEncontrado));
}

void apaga_valores_nodo(struct nodo *no){
        free(no->chaves);
        free(no->filhos);
        free(no);
        return;
}

/*Libera toda a memória alocada. Ou seja, todos os nodos são liberados, além da struct
arvoreB passada como parâmetro.*/
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