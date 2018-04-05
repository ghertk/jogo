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