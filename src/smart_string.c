#include "smart_string.h"

struct __string {
	size_t size;
	size_t capacity;
	char str[];
};

static inline void* _get_ssheader(const smart_str s){
	void *_s = s;
	_s -= sizeof(struct __string);
	return _s;
}

static struct __string* _realloc_ss(struct __string* s){
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

static struct __string* new_string_ss(const char* str, const size_t len){
	size_t capacity = len + (8 - len % 8);
	capacity *= 2;
	struct __string* s = malloc(sizeof(struct __string) + capacity + 1);
	s->size = len;
	s->capacity = capacity;
	for(size_t i = 0; i < s->size; i++) { s->str[i] = str[i]; }
	s->str[s->size] = '\0';
	return s;
}

smart_str new_n_ss(const char* str, const size_t len){
	struct __string *s = new_string_ss(str, len);
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

size_t inline getlen_ss(const smart_str str){
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
	for(size_t i = 0; i < src_len; ++i){
		if(s->size == s->capacity){ s = _realloc_ss(s); }
		s->str[s->size++] = src[i];
	}
	s->str[s->size] = '\0';

	return s->str;
}

smart_str concat_cstr_ss(smart_str dest, const char* src){
	size_t src_len = 0; // length of src
	while (*src++ != '\0'){
		++src_len;
	}
	
	struct __string* s = _get_ssheader(dest);
	for (size_t i = 0; i < src_len; ++i){
		if (s->size == s->capacity){ s = _realloc_ss(s); }
		s->str[s->size++] = src[i];
	}
	s->str[s->size] = '\0';
	
	return s->str;
}

smart_str prepend_cstr_ss(smart_str dest, const char* src) {
	size_t src_len = 0; // length of src
	while (*src++ != '\0'){
		++src_len;
	}
	
	struct __string* s = _get_ssheader(dest);
	struct __string* new_str = new_string_ss(src, src_len + s->size);
	for (size_t i = 0; i < s->size; ++i) {
		// in case capacity is not enough
		if (new_str->size == new_str->capacity) { new_str = _realloc_ss(new_str); }
		new_str->str[i+src_len] = s->str[i];
	}
	new_str->str[new_str->size] = '\0';
	
	return new_str->str;
}

smart_str substr_ss(const smart_str src, const size_t low, const size_t high){
	char* buf = malloc(sizeof(char) + (high - low));
	for(size_t i = low; i < high; i++){ buf[i - low] = src[i]; }
	smart_str s = new_n_ss(buf, (high - low));
	free(buf);
	return s;
}

int compare_ss(const smart_str s1, const smart_str s2){
	size_t min_len = (getlen_ss(s1) < getlen_ss(s2)) ? getlen_ss(s1) : getlen_ss(s2);
	for(size_t i = 0; i < min_len; ++i){
		if(s1[i] != s2[i]){
			return s1[i] - s2[i];
		}
	}
	return s1[min_len] - s2[min_len];
}