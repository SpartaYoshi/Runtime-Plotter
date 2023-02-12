#include <stdint.h>

/* DEFINITIONS */
#define BSZ 1024 // input buffer size (max length for a line)


/* STRUCTURES */

// Dataset type
typedef struct {
	int rows, cols;

	uint8_t* procs;
	float**  runtime;
} ds_t;
