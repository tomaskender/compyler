#ifndef __TOKEN_H__
#define __TOKEN_H__

typedef struct token {
    int             type;
    void*           value;
    struct token*   next;
} token_t;

#endif
