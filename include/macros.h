#ifndef INCLUDE_MACROS_H_
#define INCLUDE_MACROS_H_

#define DEBUG=1
#define debug_print(...) \
            do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#endif
