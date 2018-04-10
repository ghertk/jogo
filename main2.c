#include <SDL2/SDL.h>
#include "lista.h"
#include "personagem.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    Lista *personagens = lst_cria();
    int i = 0;
        for (i = 0; i < 5; i++) {
            Personagem *p = per_criaPersonagem("personagem.bmp", (10 * i), (10 * i), ren);
            personagens = per_insereLista(personagens, p);
        }
    SDL_RenderClear(ren);
    lst_percorre(personagens, per_desenha);
    SDL_RenderPresent(ren);
    printf("");
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}