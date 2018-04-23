#include "controle.h"

int c_eventHandler(Personagem *p) {
    SDL_Event evento;
    while (SDL_PollEvent(&evento) != 0) {
        switch (evento.type) {
            case SDL_QUIT:
                return -1;
            case SDL_KEYDOWN:
                return c_keydownHandler(evento.key, p);
            case SDL_KEYUP:
                return c_keyupHandler(evento.key, p);
        }
    }
    return 0;
}

int c_keydownHandler(SDL_KeyboardEvent keydown, Personagem *p) {
    int r = 0;
    int x = per_getVetorX(p);
    int y = per_getVetorY(p);
    switch(keydown.keysym.sym) {
        case SDLK_LEFT:
            x = -1;
            r = 1;
            break;
        case SDLK_RIGHT:
            x = 1;
            r = 2;
            break;
        case SDLK_UP:
            y = -1;
            r = 3;
            break;
        case SDLK_DOWN:
            y = 1;
            r = 4;
            break;
        case SDLK_n:
        case SDLK_ESCAPE:
            r = -1;
            break;
        case SDLK_s:
            r = 10;
            break;
    }
    per_setVetor(p, x, y);
    return r;
}

int c_keyupHandler(SDL_KeyboardEvent keyup, Personagem *p) {
    int r = 0;
    int x = per_getVetorX(p);
    int y = per_getVetorY(p);
    switch(keyup.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
            x = 0;
            r = 1;
            break;
        case SDLK_UP:
        case SDLK_DOWN:
            y = 0;
            r = 2;
            break;
    }
    per_setVetor(p, x, y);
    return r;
}