#include "controle.h"

int c_eventHandler(Personagem *p) {
    SDL_Event evento;
    while (SDL_PollEvent(&evento) != 0) {
        switch (evento.type) {
            case SDL_QUIT:
                return -1;
            case SDL_KEYDOWN:
                c_keydownHandler(evento.key, p);
                return 0;
            case SDL_KEYUP:
                c_keyupHandler(evento.key, p);
                return 0;
        }
    }
    return 0;
}

void c_keydownHandler(SDL_KeyboardEvent keydown, Personagem *p) {
    int x = per_getVetorX(p);
    int y = per_getVetorY(p);
    switch(keydown.keysym.sym) {
        case SDLK_LEFT:
            x = -1;
            break;
        case SDLK_RIGHT:
            x = 1;
            break;
        case SDLK_UP:
            y = 1;
            break;
        case SDLK_DOWN:
            y = -1;
            break;
    }
    per_setVetor(p, x, y);
}

void c_keyupHandler(SDL_KeyboardEvent keyup, Personagem *p) {
    int x = per_getVetorX(p);
    int y = per_getVetorY(p);
    switch(keyup.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
            x = 0;
            break;
        case SDLK_UP:
        case SDLK_DOWN:
            y = 0;
            break;
    }
    per_setVetor(p, x, y);
}