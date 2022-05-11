#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "token.h"

typedef struct ctx {
    token_t *tokens_head;
} ctx_t;

#endif
