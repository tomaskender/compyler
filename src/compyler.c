#include "include/token.h"
#include "include/error.h"

#include <stdio.h>

int main() {
    FILE *f = stdin;

    ctx_t context;
    context_init(&context);

    token_t *t;
    do {
        token_load(&context, f, t);
    } while(t->type != CMPLR_OK);
    return 0;
}
