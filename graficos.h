#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"

/* Carrega determinada sprite */
SDL_Texture *g_carregaTextura(char *arquivo, SDL_Renderer *r);

/* Renderiza determinda textura */
void g_renderizaTextura(SDL_Texture *t, SDL_Renderer *r, int x, int y, SDL_Rect *clip);

/* Desenha fundo */
void g_desenhaFundo(SDL_Texture *t, SDL_Renderer *r, int screenWidth, int screenHeight);

/* Carrega determinado texto e fonte */
SDL_Texture *g_carregaTexto(char *mensagem, char *arquivo, SDL_Color cor, int tamFont, SDL_Renderer *renderer);
