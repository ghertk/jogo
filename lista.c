#include "lista.h"

struct lista {
    void *item;
    Lista *prox;
};

Lista *lst_cria() {
    return NULL;
}

Lista *lst_insere(Lista *l, void *i) {
    Lista *p = (Lista *)malloc(sizeof(Lista));
    p->item = i;
    p->prox = l;
    return p;
}

Lista *lst_getProx(Lista *l) {
    return l->prox;
}

void *lst_getItem(Lista *l) {
    return l->item;
}

Lista *lst_remove(Lista *l) {
    return l;
}