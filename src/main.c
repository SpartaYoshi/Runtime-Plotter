#include <stdio.h>
#include <stdlib.h>

#include "../include/bmark.h"
#include "../include/ds.h"
#include "../include/globals.h"


int main (int argc, char *argv[]) {

	if (argc != 2) {
		printf("Use: ./runtime-plot <file>\n");
		exit(ER_ARGS);
	}

	// Setup
	ds_t ds;
	bm_t bm;

	import_data(&ds, argv[1]);

	bm.rows  = ds.rows;
	bm.cols  = ds.cols;
	bm.procs = ds.procs;
	
	alloc_benchmark(&bm);

	// Calculate benchmark metrics (speedup and efficiency)
	calc_avg_runtime(&ds, &bm);
	calc_speedup(&bm);
	calc_efficiency(&bm);

	print_benchmark(&bm);
	
	exit(0);
}

