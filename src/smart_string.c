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
	size_t cap_tmp = s->capacity;
	cap_tmp *= 2;
	struct __string* temp = realloc(s, sizeof(struct __string) + cap_tmp);
	// realloc failure
	if (temp == NULL) {
		return s;
	}
	else {
		temp->capacity = cap_tmp;
		return temp;
	}
}

static struct __string* new_string_ss(const char* str, const size_t len){

	// init with capacity
	unsigned int padding_size = sizeof(size_t);
	size_t capacity = len + (padding_size - len % padding_size);
	capacity *= 2;
	struct __string* s = malloc(sizeof(struct __string) + capacity);
	s->capacity = capacity;
	
	// init str with size
	s->size = len;
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

smart_str concat_ss(const smart_str left, const smart_str right){
	size_t right_len = getlen_ss(right);
	if(right_len <= 0){
		return left;
	}

	struct __string* s = _get_ssheader(left);
	for(size_t i = 0; i < right_len; i++){
		if(s->size == s->capacity){
			void* tmp = s;
			s = _realloc_ss(s);

			// failed to realloc
			if((void *)s == tmp) {
				break;
			}
		}
		s->str[s->size++] = right[i];
	}

	if(s->size == s->capacity) {
		void* tmp = s;
		s = _realloc_ss(s);

		if((void *)s != tmp) {
			s->str[s->size] = '\0';
		}
	}
	else {
		s->str[s->size] = '\0';
	}

	return s->str;
}

smart_str concat_cstr_ss(const smart_str left, const char* right){
	size_t right_len = 0; // length of cstr
	while (*right++ != '\0'){
		++right_len;
	}
	
	struct __string* s = _get_ssheader(left);
	for (size_t i = 0; i < right_len; ++i){
		if (s->size == s->capacity){ 
			void* tmp = s;
			s = _realloc_ss(s);

			// failed to realloc
			if((void *)s == tmp) {
				break;
			}
		}
		s->str[s->size++] = right[i];
	}
	
	if(s->size == s->capacity) {
		void* tmp = s;
		s = _realloc_ss(s);

		if((void *)s != tmp) {
			s->str[s->size] = '\0';
		}
	}
	else {
		s->str[s->size] = '\0';
	}
	
	return s->str;
}

smart_str prepend_cstr_ss(const smart_str left, const char* right) {
	size_t right_len = 0; // length of src
	while (*right++ != '\0'){
		++right_len;
	}
	
	struct __string* s = _get_ssheader(left);
	struct __string* new_str = new_string_ss(right, right_len + s->size);
	for (size_t i = 0; i < s->size; ++i) {
		// in case capacity is not enough
		if (new_str->size == new_str->capacity) { 
			void* tmp = new_str;
			new_str = _realloc_ss(new_str);

			// failed to realloc
			if((void *)new_str == tmp) {
				break;
			}
		}

		new_str->str[i+right_len] = s->str[i];
	}

	if(new_str->size == new_str->capacity) {
		void* tmp = new_str;
		new_str = _realloc_ss(new_str);

		if((void *)new_str != tmp) {
			new_str->str[new_str->size] = '\0';
		}
	}
	else {
		new_str->str[new_str->size] = '\0';
	}
	
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