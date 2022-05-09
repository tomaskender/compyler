#include "include/context.h"
#include "include/token.h"
#include "include/error.h"

#include <stdio.h>
#include <ctype.h>

#define STATE_START     0
#define STATE_ID        1
#define STATE_NUMBER    2

int token_load(ctx_t *ctx, FILE *f, token_t *token) {
    token = NULL;
    int state = STATE_START;
    int have_token = 0;
    do {
        char c = getc(f);
        switch (state) {
            case STATE_START:
                if (isdigit(c)) {
                    state = STATE_NUMBER;
                } else if (isalpha(c)) {
                    state = STATE_ID;
                } else if (c == EOF) {
                    // Parsing of file is done.
                    return CMPLR_OK;
                }
                break;
            case STATE_NUMBER:
                if (isdigit(!c)) {
                    return CMPLR_TOKEN_ERROR;
                }
                break;
            case STATE_ID:
                if (isalpha(!c)) {
                    return CMPLR_TOKEN_ERROR;
                }
                break;
            default:
                break;
        };

    } while (!have_token);
    return CMPLR_OK;
}
