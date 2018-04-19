// git push -u origin master
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "personagem.h"
#include "graficos.h"
#include "controle.h"
#include "defs.h"

int finalizarJogo(SDL_Window *j);

int main(int argc, char *argv[]) {
    // Inicializa o SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logSDLError("SDL_Init");
        return 1;
    }
    if (TTF_Init() < 0) {
        logSDLError("TTF_Init");
        SDL_Quit();
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
    Personagem *personagem = per_criaPersonagem("personagem.bmp", 0, 0, renderer);
    if (personagem == NULL) {
        logSDLError("Criar Personagem");
        SDL_DestroyRenderer(renderer);
        finalizarJogo(janela);
    }
    Lista *inimigos = lst_cria();
    int i = 0;
    srand(time(NULL));
    for (i = 0; i < 5; i++) {
        inimigos = per_insereLista(inimigos, per_criaPersonagem("personagem.bmp", rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, renderer));
    }
    SDL_Texture *background = g_carregaTextura("background.bmp", renderer);
    SDL_Color cor = { 255, 255, 255, 255 };
    SDL_Texture *texto = g_carregaTexto("Pressione qualquer tecla para iniciar.", "fonte.ttf", cor, 64, renderer);
    SDL_RenderClear(renderer);
    {
        int h, w;
        SDL_QueryTexture(texto, NULL, NULL, &w, &h);
        int x = SCREEN_WIDTH / 2 - w / 2;
        int y = SCREEN_HEIGHT / 2 - h / 2;
        g_renderizaTextura(texto, renderer, x, y);
        SDL_RenderPresent(renderer);
        while (c_eventHandler(personagem) != 0) {}
    }
    while (1) {
        SDL_RenderClear(renderer);
        // Verifica se é o evento de fechamento de janela
        if (c_eventHandler(personagem) < 0) {
            finalizarJogo(janela);
            return 0;
        }
        per_movimenta(personagem);
        Lista *l;
        for ( l = inimigos; l != NULL; l = lst_getProx(l)) {
            if (per_colidiu(personagem, (Personagem *)lst_getItem(l))) {
                inimigos = per_removeLista(inimigos, (Personagem *)lst_getItem(l));
                break;
            }
        }
        g_desenhaFundo(background, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        // Imprime o personagem
        per_desenha(personagem, renderer);
        per_desenhaLista(inimigos, renderer);
        // Mostra os objetos renderizados
        SDL_RenderPresent(renderer);
    }
    per_limpaLista(inimigos);
    per_libera(personagem);
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
