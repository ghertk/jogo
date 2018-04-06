#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "personagem.h"
#include "graficos.h"
#include "controle.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int finalizarJogo(SDL_Window *j);

int main(int argc, char *argv[]) {
    // Inicializa o SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logSDLError("SDL_Init");
        return 1;
    }
    // Cria a janela principal
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
    Personagem *personagem = per_criaPersonagem("personagem.bmp",0, 0, renderer);
    if (personagem == NULL) {
        logSDLError("Criar Personagem");
        SDL_DestroyRenderer(renderer);
        finalizarJogo(janela);
    }
    SDL_Texture *background = g_carregaTextura("background.bmp", renderer);
    while (1) {
        SDL_RenderClear(renderer);
        // Verifica se é o evento de fechamento de janela
        if (c_eventHandler(personagem) < 0) {
            finalizarJogo(janela);
            return 0;
        }
        // Imprime o personagem
        per_desenha(personagem, renderer);
        // Mostra os objetos renderizados
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    finalizarJogo(janela);
    return 0;
}

int finalizarJogo(SDL_Window *j) {
    SDL_DestroyWindow(j);
    SDL_Quit();
    exit(1);
}
