#include <stdio.h>
#include <stdlib.h>

#include "../include/calc.h"
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

	alloc_dataset(&ds);
	import_data(argv[1], &ds);

	bm.rows  = ds.rows;
	bm.cols  = ds.cols;
	bm.procs = ds.procs;

	alloc_benchmark(&bm);

	// Calculate benchmark metrics (speedup and efficiency)
	calc_speedup(&ds, &bm);
	calc_efficiency(&bm);

	//test
	printf("%f", bm.efficiency[2]);

	exit(0);
}