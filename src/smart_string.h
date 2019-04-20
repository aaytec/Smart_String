#ifndef SMART_STRING_H
#define SMART_STRING_H

#define DEF_TOKENS_CAP 4

typedef char* smart_str;
typedef char** smart_tok;

struct __string;
struct _tokens;

// void *_get_ssheader(const smart_str s);

// void* _get_stheader(const smart_tok t);
// struct __string* _realloc_ss(struct __string* s);

smart_str new_n_ss(const char* str, const size_t len);

smart_str new_ss(const char* str);

void delete_ss(smart_str str);

size_t getlen_ss(const smart_str str);

smart_str copy_ss(const smart_str src);

smart_str concat_ss(smart_str dest, const smart_str src);

smart_str substr_ss(const smart_str src, const size_t low, const size_t high);

smart_tok tokenize_ss(const smart_str src, char delim, size_t* amount);

size_t getlen_st(const smart_tok t);

void delete_st(smart_tok t);

#endif
