#include "smart_manip.h"

#define LOWER_MIN 97
#define LOWER_MAX 122
#define UPPER_MIN 65
#define UPPER_MAX 90
#define UPPER_LOWER_DIFF 32

static void _swap_ss(char* x, char* y){
  char temp = *x;
  *x = *y;
  *y = temp;
}

smart_str reverse_ss(smart_str str){
  size_t size = getlen_ss(str);
  for(size_t i = 0, j = size-1; i < j; i++, j--){
    _swap_ss(&str[i], &str[j]);
  }
  return str;
}

smart_str to_upper_ss(smart_str str){
  size_t size = getlen_ss(str);
  for(size_t i = 0; i < size; i++){
    if(*(str[i]) >= LOWER_MIN && *(str[i]) <= LOWER_MAX){
      *(str[i]) -= UPPER_LOWER_DIFF;
    }
  }
  return str;
}

smart_str to_lower_ss(smart_str str){
  size_t size = getlen_ss(str);
  for(size_t i = 0; i < size; i++){
    if(*(str[i]) >= UPPER_MIN && *(str[i]) <= UPPER_MAX){
      *(str[i]) += UPPER_LOWER_DIFF;
    }
  }
  return str;
}

smart_str insert_at_ss(smart_str str, const char* insert, size_t idx){
  size_t size = getlen_ss(str);
  if(idx <= 0){
    return prepend_cstr_ss(str, insert);
  }
  else if(idx >= size){
    return concat_cstr_ss(str, insert);
  }
  else{
    smart_str lhs = substr_ss(str, 0, idx);
    smart_str rhs = substr_ss(str, idx, size);
    lhs = concat_cstr_ss(lhs, insert);
    lhs = concat_ss(lhs, rhs);
    delete_ss(rhs);
    delete_ss(str);
    return lhs;
  }
}
