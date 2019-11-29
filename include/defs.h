#ifndef INCLUDE_DEFS_H_
#define INCLUDE_DEFS_H_


#define DEFAULT_MINE_FRACTION 0.1
#define DEBUG=1

#define debug_print(...) \
            do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#endif
