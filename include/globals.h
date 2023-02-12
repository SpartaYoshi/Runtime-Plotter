#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

/* DEFINITIONS */
#define BSZ 1024 // input buffer size (max length for a line)

// Errors
#define ER_ARGS 1
#define ER_OPEN 2

/* STRUCTURES */

// Dataset type
typedef struct {
	int rows, cols;

	uint8_t* procs;
	float**  runtime;
} ds_t;

#endif