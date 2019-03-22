#ifndef SMART_STRING_H
#define SMART_STRING_H
#include <stdlib.h>

#define DEF_TOKENS_CAP 4

typedef char* smart_string;
typedef char* smart_zstring;

typedef char** smart_tokens;

struct _string{
	size_t size;
	char str[];
};

struct __string{
	size_t size;
	size_t capacity;
	char str[];
};

struct _tokens{
	size_t size;
	char* token[];
};

void* _get_header(const smart_string s){
	void* _s = s;
        _s -= sizeof(struct _string);
	return _s;
}

void *_get_zheader(const smart_zstring s){
	void *_s = s;
	_s -= sizeof(struct __string);
	return _s;
}

void* _get_theader(const smart_tokens t){
	void* _t = t;
	_t -= sizeof(struct _tokens);
	return _t;
}

size_t getlen_tokens(const smart_tokens t){
	struct _tokens* _t = (struct _tokens* )_get_theader(t);
	return _t->size;
}

/* SMART_STRING */

smart_string new_nstring(const char* str, const size_t len){
	struct _string* s = malloc(sizeof(struct _string) + len + 1);
	s->size = len;
	for(size_t i = 0; i < s->size; i++) { s->str[i] = str[i]; }
	s->str[s->size] = '\0';
	return s->str;
}

smart_string new_string(const char* str){
	size_t len = 0;
	for(size_t i = 0; str[i] != '\0'; i++) { len++; }
	return new_nstring(str, len);
}

void delete_string(smart_string str){
	free(_get_header(str));
	str = 0;
}

size_t getlen_string(const smart_string str){
	struct _string* _s = _get_header(str);
	return _s->size;
}

smart_string copy_string(const smart_string src){
    size_t src_len = getlen_string(src);
	return new_nstring(src, src_len);
}

smart_string concat_string(smart_string dest, const smart_string src){
	size_t src_len = getlen_string(src);
    if(src_len == 0){
        return dest;
	}

    struct _string* s = _get_header(dest);
	s = realloc(s, sizeof(struct _string) + s->size + src_len + 1);
    for(size_t i = 0; i < src_len; i++){ s->str[i + s->size] = src[i]; }
    s->size += src_len;
	s->str[s->size] = '\0';

    return s->str;
}

smart_string sub_string(const smart_string src, size_t low, size_t high){
	char* buf = malloc(sizeof(char) + (high - low));
	for(size_t i = low; i < high; i++){ buf[i - low] = src[i]; }
	smart_string s = new_nstring(buf, (high - low));
	free(buf);
	return s;
}

smart_tokens tokenize_string(const smart_string src, char delim, size_t* amount){
	size_t capacity = DEF_TOKENS_CAP;
	size_t count = 0;
	struct _tokens* tokens = malloc(sizeof(struct _tokens) + sizeof(smart_string) * capacity);
	
	ssize_t low = -1;
	ssize_t high = -1;
	size_t size = getlen_string(src);

	for(size_t i = 0; i < size; i++){
		if((src[i] == delim || src[i] == '\n') && low >= 0){
			high = i;
			smart_string token = sub_string(src, low, high);
			if(count == capacity){
				capacity *= 2;
				tokens = realloc(tokens, sizeof(struct _tokens) + sizeof(smart_string) * capacity);
			}
			tokens->token[count++] = token;
			low = -1;
			high = -1;
		}
		else if (src[i] != delim && src[i] != '\n' && low < 0){ low = i; }
	}

	if(low >= 0){
		high = size;
		smart_string token = sub_string(src, low, high);
		if(count == capacity){
			capacity *= 2;
			tokens = realloc(tokens, sizeof(struct _tokens) + sizeof(smart_string) * capacity);
		}
		tokens->token[count++] = token;
	}

	*amount = count;
	tokens->size = count;
	return tokens->token;
}

void delete_tokens(smart_tokens t){
	size_t count = getlen_tokens(t);
	for(size_t i = 0; i < count; i++){
			delete_string(t[i]);
	}
	free(_get_theader(t));
}

/* SMART_ZSTRING */

smart_zstring new_nzstring(const char* str, const size_t len){
	size_t capacity = len + (8 - len % 8);
	capacity *= 2;
	struct __string* s = malloc(sizeof(struct __string) + capacity + 1);
	s->size = len;
	s->capacity = capacity;
	for(size_t i = 0; i < s->size; i++) { s->str[i] = str[i]; }
	s->str[s->size] = '\0';
	return s->str;
}

smart_zstring new_zstring(const char* str){
	size_t len = 0;
	for(size_t i = 0; str[i] != '\0'; i++) { len++; }
	return new_nzstring(str, len);
}

void delete_zstring(smart_zstring str){
	free(_get_zheader(str));
	str = 0;
}

struct __string* realloc_zstring(struct __string* s){
	s->capacity *= 2;
	return realloc(s, sizeof(struct __string) + s->capacity + 1);
}

size_t getlen_zstring(const smart_zstring str)
{
	struct __string* __s = _get_zheader(str);
	return __s->size;
}

smart_zstring copy_zstring(const smart_zstring src){
	size_t src_len = getlen_zstring(src);
	return new_nzstring(src, src_len);
}

smart_zstring concat_zstring(smart_zstring dest, const smart_zstring src){
	size_t src_len = getlen_zstring(src);
	if(src_len == 0){
		return dest;
	}

	struct __string* s = _get_zheader(dest);
	for(size_t i = 0; i < src_len; i++){
		if(s->size == s->capacity){ s = realloc_zstring(s); }
		s->str[s->size++] = src[i];
	}
	s->str[s->size] = '\0';
	
	return s->str;
}

smart_zstring sub_zstring(const smart_zstring src, const size_t low, const size_t high){
	char* buf = malloc(sizeof(char) + (high - low));
	for(size_t i = low; i < high; i++){ buf[i - low] = src[i]; }
	smart_zstring s = new_nzstring(buf, (high - low));
	free(buf);
	return s;
}

smart_tokens tokenize_zstring(const smart_zstring src, char delim, size_t* amount){
	size_t capacity = DEF_TOKENS_CAP;
	size_t count = 0;
	struct _tokens* tokens = malloc(sizeof(struct _tokens) + sizeof(smart_zstring) * capacity);
	
	ssize_t low = -1;
	ssize_t high = -1;
	size_t size = getlen_zstring(src);

	for(size_t i = 0; i < size; i++){
		if((src[i] == delim || src[i] == '\n') && low >= 0){
			high = i;
			smart_zstring token = sub_zstring(src, low, high);
			if(count == capacity){
				capacity *= 2;
				tokens = realloc(tokens, sizeof(struct _tokens) + sizeof(smart_zstring) * capacity);
			}
			tokens->token[count++] = token;
			low = -1;
			high = -1;
		}
		else if (src[i] != delim && src[i] != '\n' && low < 0){ low = i; }
	}

	if(low >= 0){
		high = size;
		smart_zstring token = sub_zstring(src, low, high);
		if(count == capacity){
			capacity *= 2;
			tokens = realloc(tokens, sizeof(struct _tokens) + sizeof(smart_zstring) * capacity);
		}
		tokens->token[count++] = token;
	}

	*amount = count;
	tokens->size = count;
	return tokens->token;
}

void delete_ztokens(smart_tokens t){
	size_t count = getlen_tokens(t);
	for(size_t i = 0; i < count; i++){
			delete_zstring(t[i]);
	}
	free(_get_theader(t));
}

#endif
