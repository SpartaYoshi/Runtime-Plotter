#include <stdlib.h>

#include "../include/globals.h"


void alloc_benchmark(bm_t *bm){
	bm->speedup    = (float *) malloc(bm->rows * sizeof(float));
	bm->efficiency = (float *) malloc(bm->rows * sizeof(float));
}


void calc_speedup(ds_t *ds, bm_t *bm){
	int i, j;
	float ts, tp;
	ts = 0;

	for (i = 0; i < ds->rows; i++){
		tp = 0;

		// Average runtimes
		if (ds->procs[i] == 1) { // Serial time
			for (j = 0; j < ds->cols-1; j++)
				ts += ds->runtime[i][j];
			ts /= ds->cols-1;
			continue;
		}

		for (j = 0; j < ds->cols-1; j++) // Parallel time
			tp += ds->runtime[i][j];
		tp /= ds->cols-1;

		bm->speedup[i] = ts / tp;
	}
}


void calc_efficiency(bm_t *bm){
	int i;

	for (i = 0; i < bm->rows; i++)
		bm->efficiency[i] = bm->speedup[i] / bm->procs[i];
}