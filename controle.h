#include <SDL2/SDL.h>
#include "personagem.h"

/* Função principal do tratamento de eventos */
int c_eventHandler(Personagem *p);

/* Trata os eventos de pressionamento de teclas */
int c_keydownHandler(SDL_KeyboardEvent keydown, Personagem *p);

/* Trata os evento de soltura de teclas*/
int c_keyupHandler(SDL_KeyboardEvent keyup, Personagem *p);