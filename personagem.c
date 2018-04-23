#include "personagem.h"

struct vetor {
    int x, y;
};

struct personagem {
    int id;
    int x, y;
    int w, h;
    Vetor movimento;
    SDL_Texture *textura;
};

Personagem *per_criaPersonagem(char *img,int x, int y, SDL_Renderer *renderer) {
    static int id = 0;
    SDL_Texture *imagem = g_carregaTextura(img, renderer);
    if (imagem == NULL) {
        return NULL;
    }
    Vetor m;
    m.x = 0;
    m.y = 0;
    Personagem *p = (Personagem *)malloc(sizeof(Personagem));
    p->id = ++id;
    p->movimento = m;
    p->textura = imagem;
    SDL_QueryTexture(p->textura, NULL, NULL, &p->w, &p->h);
    p->x = (x + p->w > SCREEN_WIDTH) ? SCREEN_WIDTH - p->w : x;
    p->y = (y + p->h > SCREEN_HEIGHT) ? SCREEN_HEIGHT - p->h : y;
    
    return p;
}


int per_getVetorX(Personagem *p) {
    return p->movimento.x;
}

int per_getVetorY(Personagem *p) {
    return p->movimento.y;
}

void per_setVetor(Personagem *p, int x, int y) {
    p->movimento.x = x;
    p->movimento.y = y;
}

void per_desenha(Personagem *p, SDL_Renderer *r) {
    int pw, ph;
    SDL_QueryTexture(p->textura, NULL, NULL, &pw, &ph);
    g_renderizaTextura(p->textura, r, p->x, p->y, NULL);
}

void per_movimenta(Personagem *p) {
    int movx = per_getVetorX(p) * 10;
    int movy = per_getVetorY(p) * 10;
    p->x += movx;
    p->y += movy;
    if (p->x < 0) {
        p->x = 0;
    } else if (p->x + p->w > SCREEN_WIDTH) {
        p->x = SCREEN_WIDTH - p->w;
    }
    if (p->y < 0) {
        p->y = 0;
    } else if (p->y + p->h > SCREEN_HEIGHT) {
        p->y = SCREEN_HEIGHT - p->h;
    }
}

Lista *per_insereLista(Lista *l, Personagem* p) {
    return lst_insere(l, (void *) p);
}

Lista *per_removeLista(Lista *l, Personagem *p) {
    Lista *atual = l;
    Lista *anterior = NULL;
    while (atual != NULL) {
        Personagem *item = (Personagem *)lst_getItem(atual);
        if (item->id == p->id) {
            per_libera(item);
            break;
        }
        anterior = atual;
        atual = lst_getProx(atual);
    }
    if (atual == NULL) {
        return l;
    }
    if (anterior == NULL) {
        l = lst_getProx(atual);
    } else {
        lst_setProx(anterior, atual);
    }
    free(atual);
    return l;
}

void per_desenhaLista(Lista *l, SDL_Renderer *renderer) {
    Lista *aux = l;
    for (aux = l; aux != NULL; aux = lst_getProx(aux)) {
        per_desenha((Personagem *)lst_getItem(aux), renderer);
    }
}

int per_colidiu(Personagem *p1, Personagem *p2) {
    if (p1->y + p1->h <= p2->y) {
        return 0;
    }
    if (p1->y >= p2->y + p2->h) {
        return 0;
    }
    if (p1->x + p1->w <= p2->x) {
        return 0;
    }
    if (p1->x >= p2->x + p2->w) {
        return 0;
    }
    return 1;
}

void per_limpaLista(Lista *l) {
    Lista *atual = l; 
    while (atual != NULL) {
        atual = per_removeLista(atual, (Personagem *)lst_getItem(atual));
    }
}

void per_libera(Personagem *p) {
    free(p);
}
