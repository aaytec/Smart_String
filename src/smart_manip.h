#ifndef SMART_STRING_H
#define SMART_STRING_H
#include "smart_string.h"

smart_str reverse_ss(smart_str str);
smart_str to_upper_ss(smart_str str);
smart_str to_lower_ss(smart_str str);
smart_str insert_at_ss(smart_str str, const char* insert, size_t idx);

#endif
