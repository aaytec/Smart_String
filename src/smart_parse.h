#ifndef SMART_PARSE_H
#define SMART_PARSE_H
#include "smart_string.h"

#define DEF_TOKENS_CAP 4

typedef char** smart_tok;
struct _tokens;

smart_tok tokenize_ss(const smart_str src, char delim, size_t* amount);
size_t getlen_st(const smart_tok t);
void delete_st(smart_tok t);

#endif