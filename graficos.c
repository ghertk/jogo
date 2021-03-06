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

void g_renderizaTextura(SDL_Texture *t, SDL_Renderer *r, int x, int y, SDL_Rect *clip) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != NULL) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(t, NULL, NULL, &dst.w, &dst.h);
    }
    SDL_RenderCopy(r, t, clip, &dst);
}

void g_desenhaFundo(SDL_Texture *t, SDL_Renderer *r, int screenWidth, int screenHeight) {
    int bw, bh;
    SDL_QueryTexture(t, NULL, NULL, &bw, &bh);
    int x, y;
    for (x = 0; x < screenWidth; x += bw) {
        for (y = 0; y < screenHeight; y += bh) {
            g_renderizaTextura(t, r, x, y, NULL);
        }
    }
}

SDL_Texture *g_carregaTexto(char *mensagem, char *arquivo, SDL_Color cor, int tamFont, SDL_Renderer *renderer) {
    TTF_Font *fonte = TTF_OpenFont(arquivo, tamFont);
    if (fonte == NULL) {
        logSDLError("TTF_OpenFont");
        return NULL;
    }
    SDL_Surface *surface = TTF_RenderText_Blended(fonte, mensagem, cor);
    if (surface == NULL) {
        TTF_CloseFont(fonte);
        logSDLError("TTF_RenderText");
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        logSDLError("CreateTexture");
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(fonte);
    return texture;
}
