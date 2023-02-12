#include <stdlib.h>

#include "../include/globals.h"


void alloc_benchmark(bm_t *bm){
	bm->avg_runtime = (float *) malloc(bm->rows * sizeof(float));
	bm->speedup     = (float *) malloc(bm->rows * sizeof(float));
	bm->efficiency  = (float *) malloc(bm->rows * sizeof(float));
}


void calc_avg_runtime(ds_t *ds, bm_t *bm){
	int i, j;
	float avg;

	for (i = 0; i < ds->rows; i++){
		avg = 0;

		for (j = 0; j < ds->cols-1; j++)
			avg += ds->runtime[i][j];

		avg /= ds->cols-1;

		bm->avg_runtime[i] = avg;

	}
}


void calc_speedup(bm_t *bm){
	int i;

	// Preassumption: first row is p=1
	for (i = 0; i < bm->rows; i++)
		bm->speedup[i] = bm->avg_runtime[0] / bm->avg_runtime[i];
}


void calc_efficiency(bm_t *bm){
	int i;

	for (i = 0; i < bm->rows; i++)
		bm->efficiency[i] = bm->speedup[i] / bm->procs[i];
}