#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "graficos.h"
#include "defs.h"

typedef struct vetor Vetor;

typedef struct personagem Personagem;

Personagem *per_criaPersonagem(char *img, int x, int y, SDL_Renderer *renderer);

int per_getVetorX(Personagem *p);

int per_getVetorY(Personagem *p);

void per_setVetor(Personagem *p,int x, int y);

void per_desenha(Personagem *p, SDL_Renderer *r);

Personagem *per_movimenta(Personagem *p);
