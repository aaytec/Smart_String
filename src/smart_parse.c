<<<<<<< HEAD
#include "smart_parse.h"
#include <stdlib.h>

#define DEF_TOKENS_CAP 4


struct _tokens{
	size_t size;
	char* token[];
};

static inline void* _get_stheader(const smart_tok t){
	void* _t = t;
	_t -= sizeof(struct _tokens);
	return _t;
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

size_t inline getlen_st(const smart_tok t){
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
=======
#include "smart_parse.h"
#include <stdlib.h>

#define DEF_TOKENS_CAP 4


struct _tokens{
	size_t size;
	char* token[];
};

void* _get_stheader(const smart_tok t){
	void* _t = t;
	_t -= sizeof(struct _tokens);
	return _t;
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
>>>>>>> 5239bbcf657b34b08c4a61c9e654d788d355e6d1
