#include "personagem.h"

struct vetor {
    int x, y;
};

struct personagem {
    int x, y;
    int w, h;
    Vetor movimento;
    SDL_Texture *textura;
};

Personagem *per_criaPersonagem(char *img,int x, int y, SDL_Renderer *renderer) {
    SDL_Texture *imagem = g_carregaTextura(img, renderer);
    if (imagem == NULL) {
        return NULL;
    }
    Vetor m;
    m.x = 0;
    m.y = 0;
    Personagem *p = (Personagem *)malloc(sizeof(Personagem));
    p->movimento = m;
    p->x = x;
    p->y = y;
    p->textura = imagem;
    SDL_QueryTexture(p->textura, NULL, NULL, &p->w, &p->h);
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
    g_renderizaTextura(p->textura, r, p->x, p->y);
}

Personagem *per_movimenta(Personagem *p) {
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
    return p;
}

Lista *per_insereLista(Lista *l, Personagem* p) {
    return lst_insere(l, (void *) p);
}

void per_desenhaLista(Lista *l, SDL_Renderer *renderer) {
    Lista *aux = l;
    for (aux = l; aux != NULL; aux = lst_getProx(aux)) {
        per_desenha((Personagem *)lst_getItem(aux), renderer);
    }
}
