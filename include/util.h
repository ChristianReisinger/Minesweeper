#ifndef INCLUDE_UTIL_H_
#define INCLUDE_UTIL_H_

typedef enum {
	SUCCESS,
	MEMORY_ERR,
	OVERFLOW_ERR
} error;

unsigned random_unsigned_from_zero_to_max(unsigned max);

#endif
