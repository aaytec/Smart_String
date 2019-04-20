#ifndef SMART_STRING_H
#define SMART_STRING_H
#include "smart_string.h"
#include <stdlib.h>

#define DEF_TOKENS_CAP 4

typedef char* smart_str;
typedef char** smart_tok;

struct __string{
	size_t size;
	size_t capacity;
	char str[];
};

struct _tokens{
	size_t size;
	char* token[];
};

void *_get_ssheader(const smart_str s){
	void *_s = s;
	_s -= sizeof(struct __string);
	return _s;
}

void* _get_stheader(const smart_tok t){
	void* _t = t;
	_t -= sizeof(struct _tokens);
	return _t;
}

struct __string* _realloc_ss(struct __string* s){
	struct __string* temp = realloc(s, sizeof(struct __string) + s->capacity + 1);
	// realloc failure
	if (temp == NULL) {
		return s;
	}
	else {
		s->capacity *= 2;
		return temp;
	}
}

/* SMART_ZSTRING */

smart_str new_n_ss(const char* str, const size_t len){
	size_t capacity = len + (8 - len % 8);
	capacity *= 2;
	struct __string* s = malloc(sizeof(struct __string) + capacity + 1);
	s->size = len;
	s->capacity = capacity;
	for(size_t i = 0; i < s->size; i++) { s->str[i] = str[i]; }
	s->str[s->size] = '\0';
	return s->str;
}

smart_str new_ss(const char* str){
	size_t len = 0;
	for(size_t i = 0; str[i] != '\0'; i++) { len++; }
	return new_n_ss(str, len);
}

void delete_ss(smart_str str){
	free(_get_ssheader(str));
	str = 0;
}

size_t getlen_ss(const smart_str str)
{
	struct __string* __s = _get_ssheader(str);
	return __s->size;
}

smart_str copy_ss(const smart_str src){
	size_t src_len = getlen_ss(src);
	return new_n_ss(src, src_len);
}

smart_str concat_ss(smart_str dest, const smart_str src){
	size_t src_len = getlen_ss(src);
	if(src_len == 0){
		return dest;
	}

	struct __string* s = _get_ssheader(dest);
	for(size_t i = 0; i < src_len; i++){
		if(s->size == s->capacity){ s = _realloc_ss(s); }
		s->str[s->size++] = src[i];
	}
	s->str[s->size] = '\0';

	return s->str;
}

smart_str substr_ss(const smart_str src, const size_t low, const size_t high){
	char* buf = malloc(sizeof(char) + (high - low));
	for(size_t i = low; i < high; i++){ buf[i - low] = src[i]; }
	smart_str s = new_n_ss(buf, (high - low));
	free(buf);
	return s;
}

smart_tok tokenize_ss(const smart_str src, char delim, size_t* amount){
	size_t capacity = DEF_TOKENS_CAP;
	size_t count = 0;
	struct _tokens* tokens = malloc(sizeof(struct _tokens) + sizeof(smart_str) * capacity);

	ssize_t low = -1;
	ssize_t high = -1;
	size_t size = getlen_ss(src);

	for(size_t i = 0; i < size; i++){
		if((src[i] == delim || src[i] == '\n') && low >= 0){
			high = i;
			smart_str token = substr_ss(src, low, high);
			if(count == capacity){
				capacity *= 2;
				tokens = realloc(tokens, sizeof(struct _tokens) + sizeof(smart_str) * capacity);
			}
			tokens->token[count++] = token;
			low = -1;
			high = -1;
		}
		else if (src[i] != delim && src[i] != '\n' && low < 0){ low = i; }
	}

	if(low >= 0){
		high = size;
		smart_str token = substr_ss(src, low, high);
		if(count == capacity){
			capacity *= 2;
			tokens = realloc(tokens, sizeof(struct _tokens) + sizeof(smart_str) * capacity);
		}
		tokens->token[count++] = token;
	}

	*amount = count;
	tokens->size = count;
	return tokens->token;
}

size_t getlen_st(const smart_tok t){
	struct _tokens* _t = (struct _tokens* )_get_stheader(t);
	return _t->size;
}

void delete_st(smart_tok t){
	size_t count = getlen_st(t);
	for(size_t i = 0; i < count; i++){
			delete_ss(t[i]);
	}
	free(_get_stheader(t));
}

#endif
