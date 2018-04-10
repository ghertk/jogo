#include <SDL2/SDL.h>
#include "defs.h"

/* Carrega determinada sprite */
SDL_Texture *g_carregaTextura(char *arquivo, SDL_Renderer *r);

/* Renderiza determinda textura */
void g_renderizaTextura(SDL_Texture *t, SDL_Renderer *r, int x, int y);

/* Desenha fundo */
void g_desenhaFundo(SDL_Texture *t, SDL_Renderer *r, int screenWidth, int screenHeight);
