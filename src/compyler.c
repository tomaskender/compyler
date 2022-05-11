#include "include/token_functions.h"
#include "include/context_functions.h"
#include "include/error.h"
#include "include/types.h"

#include <stdio.h>

int main() {
    FILE *f = stdin;

    ctx_t context;
    context_init(&context);

    token_t *t;
    int return_code;
    do {
        return_code = token_load(&context, f, &t);
    } while(return_code == ERR_OK && t->type != TYPE_EOF);

    context_deinit(&context);
    return 0;
}
