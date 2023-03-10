#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>


/* DEFINITIONS */
#define BSZ 1024 // input buffer size (max length for a line)

// Errors
#define ER_ARGS 1
#define ER_OPEN 2
#define ER_READ 3


/* MACROS */
#define LENGTH(x) ( sizeof(x) / sizeof((x)[0]) )


/* STRUCTURES */
// Dataset type
typedef struct {
	int rows, cols;

	uint16_t* procs;
	float**  runtime;
} ds_t;

// Benchmark type
typedef struct {
	int rows, cols;

	uint16_t* procs;
	float* 	 avg_runtime;
	float*   speedup;
	float*   efficiency;
} bm_t;

#endif