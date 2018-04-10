#include "defs.h"

void logSDLError(char *msg) {
    FILE *log = fopen("Error.log", "a+");
    fprintf(log, "%s: Error: %s\n", msg, SDL_GetError());
}