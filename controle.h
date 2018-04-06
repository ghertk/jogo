#include <SDL2/SDL.h>
#include "utils.h"
#include "personagem.h"

int c_eventHandler(Personagem *p);

void c_keydownHandler(SDL_KeyboardEvent keydown, Personagem *p);

void c_keyupHandler(SDL_KeyboardEvent keyup, Personagem *p);