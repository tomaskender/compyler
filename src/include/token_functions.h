#ifndef __TOKEN_FUNCTIONS_H__
#define __TOKEN_FUNCTIONS_H__

#include "context.h"
#include "token.h"

#include <stdio.h>

int token_load(ctx_t *ctx, FILE *f, token_t **token);

#endif
