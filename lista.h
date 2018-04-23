#include <stdlib.h>

/* Lista encadeada genérica */
typedef struct lista Lista;

/* Cria um lista */
Lista *lst_cria();

/* Insere um item na lista */
Lista *lst_insere(Lista *l, void *i);

/* Retorna o proximo elemento de uma lista.
 * Utilizada para iterar por uma lista em arquivos externos
 */
Lista *lst_getProx(Lista *l);

/* Retorna o ponteiro para o elemento de lista.
 * Utilizada para pegar o valor de um item da lista
 */
void *lst_getItem(Lista *l);

/* Remove determinado item da lista */
Lista *lst_remove(Lista *l);

/* Altera o valor do campo prox para determiando elemento */
void lst_setProx(Lista *anterior, Lista *atual);
