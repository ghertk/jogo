// utils.c
#include "utils.h"

void logSDLError(char *msg) {
    printf("%s: Error: %s\n", msg, SDL_GetError());
}