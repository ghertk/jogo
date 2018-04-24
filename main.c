/* Fonte utilizada para os textos: alterebro pixel font
 * Desenvolvido por: Ghért Bergler König
 */
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "personagem.h"
#include "graficos.h"
#include "controle.h"
#include "defs.h"

int finalizarJogo(SDL_Window *j);

int main(int argc, char *argv[]) {
    // Inicializa o SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        logSDLError("SDL_Init");
        return 1;
    }

    // Iniciliza o sistema de fontes
    if (TTF_Init() < 0) {
        logSDLError("TTF_Init");
        SDL_Quit();
        return 1;
    }

    // Cria a janela principal
    SDL_Window *janela = SDL_CreateWindow("Colete os Itens", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
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

    // Criação das variáveis
    Lista *moeda = NULL;
    Personagem *personagem = NULL;
    SDL_Texture *background = NULL;

    srand(time(NULL));
    int jogarNovamente = 0;
    do {
        // Inicializa o personagem jogavel
        personagem = per_criaPersonagem("personagem.bmp", rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, renderer);
        if (personagem == NULL) {
            logSDLError("Criar Personagem");
            SDL_DestroyRenderer(renderer);
            finalizarJogo(janela);
        }

        // Inicializa a lista de moedas e adiciona 5 itens nela
        moeda = lst_cria();
        int i = 0;
        for (i = 0; i < 5; i++) {
            moeda = per_insereLista(moeda, per_criaPersonagem("moeda.bmp", rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, renderer));
            if (per_colidiu(personagem, (Personagem *)lst_getItem(moeda))) {
                per_movXY((Personagem *)lst_getItem(moeda));
            }
            per_colidiuLista(lst_getProx(moeda), (Personagem *)lst_getItem(moeda));
        }

        // Carrega a imagem de fundo
        background = g_carregaTextura("background.bmp", renderer);
        
        // Inicializa a cor de fonte como branco
        SDL_Color cor = { 255, 255, 255, 255 };
        // Inicializa o texto do menu
        SDL_Texture *texto = g_carregaTexto("Pressione qualquer tecla para iniciar.", "fonte.ttf", cor, 64, renderer);
        SDL_RenderClear(renderer);
        
        Uint32 startTime = 0;
        int x = 0, y = 0;
        int h, w;
        // Renderiza texto do menu no centro do canto inferior da tela de menu
        SDL_QueryTexture(texto, NULL, NULL, &w, &h);
        x = SCREEN_WIDTH / 2 - w / 2;
        y = SCREEN_HEIGHT - h - 10;
        g_renderizaTextura(texto, renderer, x, y, NULL);

        // Carrega a imagem das setas
        int iW = 75, iH = 75;
        SDL_Rect clips[4];
        for (i = 0; i < 4; ++i) {
            clips[i].x = i * iW;
            clips[i].y = 0;
            clips[i].w = iW;
            clips[i].h = iH;
        }

        // Renderiza setas no centro da tela de menu
        x = SCREEN_WIDTH / 2 - iW / 2;
        y = SCREEN_HEIGHT / 2 - iH / 2;
        g_renderizaTextura(g_carregaTextura("setas.bmp", renderer), renderer, x - 100, y, &clips[0]);
        g_renderizaTextura(g_carregaTextura("setas.bmp", renderer), renderer, x, y - 100, &clips[1]);
        g_renderizaTextura(g_carregaTextura("setas.bmp", renderer), renderer, x, y, &clips[2]);
        g_renderizaTextura(g_carregaTextura("setas.bmp", renderer), renderer, x + 100, y, &clips[3]);

        // Mostra os elementos do menu
        SDL_RenderPresent(renderer);
        while (c_eventHandler(personagem) == 0) {}
        startTime = SDL_GetTicks();

        // Inicia variáveis
        int segundos = 0;
        int pontos = 0;
        char buffer[50];
        char num[6];
        int executando = 1;
        while (executando) {
            // Limpa a tela para um novo desenho
            SDL_RenderClear(renderer);
            // Verifica se é o evento de encerramento do jogo
            if (c_eventHandler(personagem) < 0) {
                executando = 0;
            }

            // Executa a movimentação e detecção de colisão
            per_movimenta(personagem);
            Lista *l;
            for ( l = moeda; l != NULL; l = lst_getProx(l)) {
                if (per_colidiu(personagem, (Personagem *)lst_getItem(l))) {
                    moeda = per_removeLista(moeda, (Personagem *)lst_getItem(l));
                    moeda = per_insereLista(moeda, per_criaPersonagem("moeda.bmp", rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, renderer));
                    if (per_colidiu(personagem, (Personagem *)lst_getItem(moeda))) {
                        per_movXY((Personagem *)lst_getItem(moeda));
                    }
                    per_colidiuLista(lst_getProx(moeda), (Personagem *)lst_getItem(moeda));
                    pontos++;
                    break;
                }
            }

            // Desenha o fundo
            g_desenhaFundo(background, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            // Imprime o personagem
            per_desenha(personagem, renderer);
            // Imprime as moedas
            per_desenhaLista(moeda, renderer);

            // Faz o cálculo do tempo e imprime no canto superior esquerdo da tela
            segundos = (int)(SDL_GetTicks() - startTime) / 1000;
            int tempoRestante = 90 - segundos;
            strcpy(buffer, "Tempo Restante: ");
            SDL_itoa(tempoRestante, num, 10);
            strcat(buffer, num);
            texto = g_carregaTexto(buffer, "fonte.ttf", cor, 64, renderer);
            SDL_QueryTexture(texto, NULL, NULL, &w, &h);
            x = 0;
            y = 0;
            g_renderizaTextura(texto, renderer, x, y, NULL);
            
            // Verifica se o tempo acabou
            if (segundos > 90) {
                executando = 0;
            }
            
            // Imprime a pontuação na parte superior direita da tela
            strcpy(buffer, "Pontos: ");
            SDL_itoa(pontos, num, 10);
            strcat(buffer, num);
            texto = g_carregaTexto(buffer, "fonte.ttf", cor, 64, renderer);
            SDL_QueryTexture(texto, NULL, NULL, &w, &h);
            x = SCREEN_WIDTH - w;
            y = 0;
            g_renderizaTextura(texto, renderer, x, y, NULL);
            
            // Mostra os objetos renderizados
            SDL_RenderPresent(renderer);
        }
        // Imprime a pontuação no centro da tela
        SDL_RenderClear(renderer);
        strcpy(buffer, "Total de Pontos: ");
        SDL_itoa(pontos, num, 10);
        strcat(buffer, num);
        texto = g_carregaTexto(buffer, "fonte.ttf", cor, 64, renderer);
        SDL_QueryTexture(texto, NULL, NULL, &w, &h);
        x = SCREEN_WIDTH / 2 - w / 2;
        y = SCREEN_HEIGHT / 2 - h / 2;
        g_renderizaTextura(texto, renderer, x, y, NULL);
        
        // Imprime a mensagem de encerramento do jogo na parte inferior da tela
        texto = g_carregaTexto("Jogar novamente? (S/N)", "fonte.ttf", cor, 64, renderer);
        SDL_QueryTexture(texto, NULL, NULL, &w, &h);
        x = SCREEN_WIDTH / 2 - w / 2;
        y = SCREEN_HEIGHT - h - 10;
        g_renderizaTextura(texto, renderer, x, y, NULL);
        SDL_RenderPresent(renderer);
        
        // Limpa o buffer de eventos
        while (c_eventHandler(personagem) != 0) {}
        // Da alguns segundos para o jogador ver os pontos
        SDL_Delay(1000);
        // Aguarda o usuário apertar S para reiniciar ou N, ESC e botão de fechar janela para sair.
        while (1){
            int codigo = c_eventHandler(personagem);
            if (codigo == 10) {
                jogarNovamente = 1;
                break;
            } else if (codigo < 0) {
                jogarNovamente = 0;
                break;
            }
        }
        // Libera a memória para uma próxima execução ou encerramento do jogo.
        per_limpaLista(moeda);
        per_libera(personagem);
        SDL_DestroyTexture(background);
    } while (jogarNovamente);    

    // Limpa os dados de execução e encerra o jogo
    SDL_DestroyRenderer(renderer);
    finalizarJogo(janela);
    return 0;
}

int finalizarJogo(SDL_Window *j) {
    SDL_DestroyWindow(j);
    SDL_Quit();
}
