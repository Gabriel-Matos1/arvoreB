#ifndef _fila_t_H
#define _fila_t_H

struct nod {
    struct nodo *x;
    struct nod *prox;
};

struct fila {
    struct nod *ini;
    struct nod *fim;
    int tamanho;
};

/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
struct fila *fila_cria ();

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (struct fila **fila);

/* 
 * Insere dado na fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (struct fila *fila, struct nodo *folha);

/* 
 * Remove dado da fila (politica FIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (struct fila *fila, struct nodo **atual);
 
/* Retorna o numero de elementos da pilha, que pode ser 0. */
int fila_tamanho (struct fila *fila);

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (struct fila *fila);

#endif
