#include "personagem.h"

struct vetor {
    int x, y;
};

struct personagem {
    int x, y;
    Vetor movimento;
    SDL_Texture *textura;
};

Personagem *per_criaPersonagem(char *img,int x, int y, SDL_Renderer *renderer) {
    SDL_Texture *imagem = g_carregaTextura("personagem.bmp", renderer);
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
