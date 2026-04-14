#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
struct fila *fila_cria ()
{
   struct fila *f = malloc(sizeof(struct fila));   /* aloca memoria para a nova fila */
   if (f == NULL)
     return NULL;

   f->ini = NULL;   
   f->tamanho = 0;   /* inicia com tamanho 0 */

   return f;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (struct fila **fila)
{
   struct nod *f, *aux;
   f = (*fila)->ini;   /* ponteiro aponta para o inicio da fila */
   while (f != NULL)   /* sai do laço quando inicio apontar para NULL, ou seja, não tem próximo elemento na fila */ 
   {
     aux = f;   /* auxiliar é criado para que a memoria possa ser destruida mas 'prox' não seja perdido */
     f = f->prox;   /* p, que é inicio, aponta para o próximo nod da lista */
     free(aux);   /* desalocamos aux que aponta para o antigo inicio */ 
   }

   free(*fila);
   *fila = NULL;
     
   return;
}

/* 
 * Insere folha na fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (struct fila *fila, struct nodo *folha)
{
   if (fila == NULL)   /* retorna 0 em caso de fila vazia */
     return 0;

   struct nod *novonod = malloc(sizeof(struct nod));   /* verifica se existe memoria para um novo nod */

   if (novonod == NULL)   /* retorna 0 em caso de não ter espaço para nod */
     return 0;

   if (fila->tamanho == 0)  /* caso não exista nod */ 
   {
     fila->ini = novonod;  /* inicio e fim apontaram para o mesmo nod adicionado */
     fila->fim = novonod;
     novonod->x = folha;
     fila->fim->prox = NULL;  /* prox prox será null para fim e ini, já q estão no mesmo nod */
     fila->ini->prox = NULL;
     fila->tamanho++;

    return 1;
   }
   
   fila->fim->prox = novonod;  /* caso a fila contenha nod */
   novonod->x = folha;  
   fila->fim = novonod;   /* novo nod será o ultimo da fila */
   fila->fim->prox = NULL;   /* ele apontará para null (ele é o ultimo da fila) */
   fila->tamanho++;
   
   return 1;
}

/* 
 * Remove folha da fila (politica FIFO) e retorna o elemento 
 * no parametro folha. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (struct fila *fila, struct nodo **folha)
{
   if (fila->tamanho == 0)  /* caso a fila não tenha nods, retorna 0 */
     return 0;
   
   struct nod *f = fila->ini;  /* cria-se um novo para apontar para inicio */
   *folha = f->x;   /* folha será a x do ponteiro para o qual f aponta */
   fila->ini = fila->ini->prox; /* o segundo elemento da fila se torna o primeiro */
   fila->tamanho--;
   free(f); /* desaloca o primeiro elemento */

   return 1;
}
 
/* Retorna o numero de elementos da fila, que pode ser 0. */
int fila_tamanho (struct fila *fila)
{
   return fila->tamanho;
}

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (struct fila *fila)
{
   if (fila->tamanho == 0) 
      return 1;
   else 
      return 0;
}

