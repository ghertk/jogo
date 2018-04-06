#include "graficos.h"

SDL_Texture *g_carregaTextura(char *arquivo, SDL_Renderer *r) {
    SDL_Texture *textura = NULL;
    SDL_Surface *imagem = SDL_LoadBMP(arquivo);
    if (imagem != NULL) {
        textura = SDL_CreateTextureFromSurface(r, imagem);
        SDL_FreeSurface(imagem);
        if (textura == NULL) {
            logSDLError("CreateTextureFromSurface");
        }
    } else {
        logSDLError("LoadBMP");
    }
    return textura;
}

void g_renderizaTextura(SDL_Texture *t, SDL_Renderer *r, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(t, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(r, t, NULL, &dst);
}

void g_desenhaFundo(SDL_Texture *t, SDL_Renderer *r, int screenWidth, int screenHeight) {
    int bw, bh;
    SDL_QueryTexture(t, NULL, NULL, &bw, &bh);
    int x, y;
    for (x = 0; x < screenWidth; x += bw) {
        for (y = 0; y < screenHeight; y += bh) {
            g_renderizaTextura(t, r, x, y);
        }
    }
}
