#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "context.h"

#include <stdio.h>

typedef struct token {
    int     type;
    char*   name;
} token_t;

int token_load(ctx_t *ctx, FILE *f, token_t *token);

#endif
