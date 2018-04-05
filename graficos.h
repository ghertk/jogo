#include <SDL2/SDL.h>
#include "utils.h"

SDL_Texture *g_carregaTextura(char *arquivo, SDL_Renderer *r);

void g_renderizaTextura(SDL_Texture *t, SDL_Renderer *r, int x, int y);