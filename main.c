#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "graficos.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int finalizarJogo(SDL_Window *j);

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logSDLError("SDL_Init");
        return 1;
    }
    SDL_Window *janela = SDL_CreateWindow("Jogo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (janela == NULL) {
        logSDLError("CreateWindow");
        SDL_Quit();
        return -1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        logSDLError("CreateRenderer");
        finalizarJogo(janela);
        return 1;
    }
    SDL_Event e;
    SDL_Texture *background = g_carregaTextura("background.bmp", renderer);
    SDL_Texture *imagem = g_carregaTextura("personagem.bmp", renderer);
    if (imagem == NULL || background == NULL) {
        logSDLError("CarregaTextura");
        SDL_DestroyRenderer(renderer);
        finalizarJogo(janela);
        return 1;
    }
    while (1) {
        SDL_RenderClear(renderer);
        int bw, bh;
        int x, y;
        SDL_QueryTexture(background, NULL, NULL, &bw, &bh);
        for (x = 0; x < SCREEN_WIDTH; x += bw) {
            for (y = 0; y < SCREEN_HEIGHT; y += bh){
                g_renderizaTextura(background, renderer, x, y);
            }
        }
        int iw, ih;
        SDL_QueryTexture(imagem, NULL, NULL, &iw, &ih);
        int ix = SCREEN_WIDTH / 2 - iw / 2;
        int iy = SCREEN_HEIGHT / 2 - ih / 2;
        g_renderizaTextura(imagem, renderer, ix, iy);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                finalizarJogo(janela);
                exit(0);
            }
        }
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(imagem);
    SDL_DestroyRenderer(renderer);
    finalizarJogo(janela);
    return 0;
}

int finalizarJogo(SDL_Window *j) {
    SDL_DestroyWindow(j);
    SDL_Quit();
}
