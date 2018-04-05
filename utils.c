#include "utils.h"

void logSDLError(char *msg) {
    /* s */printf(/* "erros.log",  */"%s: Error: %s\n", msg, SDL_GetError());
}