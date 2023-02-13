#include "errno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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


void print_benchmark(bm_t *bm){
	int i; 
	printf("#procs\truntime\t\t\tspeedup\t\t\tefficiency\n");
	printf("#=====\t=======\t\t\t=======\t\t\t==========\n");

	for (i = 0; i < bm->rows; i++)
		printf("%d\t%.6f\t\t%.6f\t\t%.6f\n", bm->procs[i], bm->avg_runtime[i], bm->speedup[i], bm->efficiency[i]);
}

void export_data(bm_t *bm){
	FILE *fp;
	struct stat sb;
	int i;

	// Create output folder (if not exists)
	char *dir = "./out";
    if (stat(dir, &sb) != 0 || !S_ISDIR(sb.st_mode)){
		mode_t perms = 0777 - umask(umask(0)); // Get umask and apply inverse to new dir
		mkdir(dir, perms);
	}
	
	// Open file to write
	fp = fopen("./out/results.dat", "w");
	if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror( errno ));
        exit(ER_OPEN);
    }


	// Export data
	fprintf(fp, "#procs\truntime\t\t\tspeedup\t\t\tefficiency\n");
	fprintf(fp, "#=====\t=======\t\t\t=======\t\t\t==========\n");

	for (i = 0; i < bm->rows; i++)
		fprintf(fp, "%d\t%.6f\t\t%.6f\t\t%.6f\n", bm->procs[i], bm->avg_runtime[i], bm->speedup[i], bm->efficiency[i]);

	fclose(fp);
}