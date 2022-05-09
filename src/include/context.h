#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "error.h"

typedef struct ctx {
    int state;
} ctx_t;

int context_init(ctx_t *context) { return CMPLR_OK; }

#endif
