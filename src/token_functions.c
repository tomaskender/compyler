#include "include/token_functions.h"
#include "include/context.h"
#include "include/token.h"
#include "include/error.h"
#include "include/cleanup.h"
#include "include/types.h"
#include "include/context.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#define STATE_START                 0
#define STATE_ID                    1
#define STATE_STRING_SINGLE_QUOTE   2
#define STATE_STRING_DOUBLE_QUOTE   3
#define STATE_LONG                  4
#define STATE_HEXA                  5
#define STATE_DOUBLE                6

int create_token_with_value(
    ctx_t *ctx,
    int type,
    void *value,
    token_t **token)
{
    size_t size;
    *token = malloc(sizeof(token_t));

    if (!*token)
    {
        error_and_cleanup(ctx, ERR_MALLOC);
    }

    (*token)->type = type;

    switch (type) {
        case TYPE_ID:
            size = strlen(value) * sizeof(char);
            break;
        case TYPE_STRING:
            size = strlen(value) * sizeof(char);
            break;
        case TYPE_LONG:
            size = sizeof(long);
            break;
        case TYPE_DOUBLE:
            size = sizeof(double);
            break;
        case TYPE_EOF:
        case TYPE_LEFT_BRACKET:
        case TYPE_RIGHT_BRACKET:
        case TYPE_COLON:
            size = 0;
            break;
        default:
            assert(0);
    };
    
    if (size) {
        (*token)->value = malloc(size);
        if (!(*token)->value)
            error_and_cleanup(ctx, ERR_MALLOC);
        memcpy((*token)->value, value, size);
    }
    return ERR_OK;
}

int token_load(ctx_t *ctx, FILE *f, token_t **token) {
    int state = STATE_START;
    char buffer[256] = "\0";

    *token = NULL;
    
    do {
        char c = getc(f);
        switch (state) {\
            case STATE_START:
            {
                if (isspace(c)) {
                    // no token here
                } else if (isdigit(c)) {
                    ungetc(c, f);
                    state = STATE_LONG;
                } else if (isalpha(c)) {
                    ungetc(c, f);
                    state = STATE_ID;
                } else {
                    switch (c) {
                        case EOF: create_token_with_value(ctx, TYPE_EOF, NULL, token); break;
                        case '(': create_token_with_value(ctx, TYPE_LEFT_BRACKET, NULL, token); break;
                        case ')': create_token_with_value(ctx, TYPE_RIGHT_BRACKET, NULL, token); break;
                        case ':': create_token_with_value(ctx, TYPE_COLON, NULL, token); break;
                        case '\'': state = STATE_STRING_SINGLE_QUOTE; break;
                        case '"': state = STATE_STRING_DOUBLE_QUOTE; break;
                        default: return ERR_SYNTAX;
                    };
                }
                break;
            };
            case STATE_ID:
            {
                if (isalpha(c)) {
                    int len = strlen(buffer);
                    buffer[len] = c;
                    buffer[len+1] = '\0';
                } else if (isspace(c) || c == '=' || c == '(') {
                    ungetc(c, f);
                    create_token_with_value(ctx, TYPE_ID, buffer, token);
                } else {
                    error_and_cleanup(ctx, ERR_SYNTAX);
                }
                break;
            };
            case STATE_STRING_SINGLE_QUOTE:
            {
                if (c != '\'' && c != '\n') {
                    int len = strlen(buffer);
                    buffer[len] = c;
                    buffer[len+1] = '\0';
                } else if (c == '\'') {
                    create_token_with_value(ctx, TYPE_STRING, buffer, token);
                } else {
                    error_and_cleanup(ctx, ERR_SYNTAX);
                }
                break;
            };
            case STATE_STRING_DOUBLE_QUOTE:
            {
                if (c != '"' && c != '\n') {
                    int len = strlen(buffer);
                    buffer[len] = c;
                    buffer[len+1] = '\0';
                } else if (c == '"') {
                    create_token_with_value(ctx, TYPE_STRING, buffer, token);
                } else {
                    error_and_cleanup(ctx, ERR_SYNTAX);
                }
                break;
            };
            case STATE_LONG:
            {
                if (isdigit(c) || c == '.') {
                    int len = strlen(buffer);
                    buffer[len] = c;
                    buffer[len+1] = '\0';
                    if (c == '.')
                        state = STATE_DOUBLE;
                } else if (c == 'x' && strcmp(buffer, "0") == 0) {
                    buffer[0] = '\0';
                    state = STATE_HEXA;
                } else if (isspace(c)){
                    char *ptr;
                    long value = strtol(buffer, &ptr, 10);
                    create_token_with_value(ctx, TYPE_LONG, &value, token);
                } else {
                    error_and_cleanup(ctx, ERR_SYNTAX);
                }
                break;
            };
            case STATE_DOUBLE:
            {
                if (isdigit(c)) {
                    int len = strlen(buffer);
                    buffer[len] = c;
                    buffer[len+1] = '\0';
                } else if (isspace(c)){
                    char *ptr;
                    double value = strtod(buffer, &ptr);
                    create_token_with_value(ctx, TYPE_DOUBLE, &value, token);
                } else {
                    error_and_cleanup(ctx, ERR_SYNTAX);
                }
                break;
            };
            case STATE_HEXA:
            {
                // TODO
                break;
            }
            default:
                break;
        };

    } while (!*token);

    return ERR_OK;
}
