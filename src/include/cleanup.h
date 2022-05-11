#ifndef __CLEANUP_H__
#define __CLEANUP_H__

#include "error.h"
#include "context_functions.h"

#include <stdlib.h>

void error_and_cleanup(ctx_t *ctx, int exit_code) {
    context_deinit(ctx);
    fprintf(stderr, "Error occured, exiting with code %i\n", exit_code);
    exit(exit_code);
}

#endif
