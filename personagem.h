#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "graficos.h"
#include "defs.h"
#include "lista.h"

/* Estrutura utilisada para determinar a direção que o personagem esta andando */
typedef struct vetor Vetor;

/* Estrutura que armazena os dados do personagem */
typedef struct personagem Personagem;

/* Função que cria personagems */
Personagem *per_criaPersonagem(char *img, int x, int y, SDL_Renderer *renderer);

/* Função que retorna o valor de movimentação no eixo x do vetor */
int per_getVetorX(Personagem *p);

/* Função que retorna o valor de movimentação no eixo y do vetor */
int per_getVetorY(Personagem *p);

/* Coloca o valor de movimento nos eixos x e y no vetor */
void per_setVetor(Personagem *p,int x, int y);

/* Desenha determinado personagem na tela */
void per_desenha(Personagem *p, SDL_Renderer *r);

/* Movimenta o personagem */
 void per_movimenta(Personagem *p);

/* Insere determinado personagem na lista */
Lista *per_insereLista(Lista *l, Personagem *p);

Lista *per_removeLista(Lista *l, Personagem *p);

/* Percorre a lista e desenha os personagens */
void per_desenhaLista(Lista *l, SDL_Renderer *renderer);

int per_colidiu(Personagem *p1, Personagem *p2);