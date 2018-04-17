#include <stdlib.h>

/* Lista encadeada generica */
typedef struct lista Lista;

/* Cria um lista */
Lista *lst_cria();

/* Insere um item na lista */
Lista *lst_insere(Lista *l, void *i);

/* Retorna o proximo elemento de uma lista.
 * Utilizada para iterar por uma lista fora do arquivo de lista
 */
Lista *lst_getProx(Lista *l);

/* Retorna o ponteiro para o elemento de lista.
 * Utilizada para pegar o valor de um item da lista
 */
void *lst_getItem(Lista *l);

/* Remove determinado item da lista */
Lista *lst_remove(Lista *l);

void lst_setProx(Lista *anterior, Lista *atual);
