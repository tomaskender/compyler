#include "include/context_functions.h"
#include "include/token.h"
#include "include/error.h"

#include <stdlib.h>

int context_init(ctx_t *context) {
    context->tokens_head = NULL;
    return ERR_OK;
}

int context_deinit(ctx_t *context) {
    token_t *current_token = context->tokens_head;
    token_t *next_token;
    while(current_token) {
        next_token = current_token->next;
        if (current_token->value)
            free(current_token->value);
        free(current_token);
        current_token = next_token;
    }
    return ERR_OK;
}
