#include <stdio.h>
#include <stdlib.h>

#include "../include/calc.h"
#include "../include/ds.h"
#include "../include/globals.h"

void print_matrix(float **m, int m_rows, int m_cols){
    
    int col, row;
    
    for (row = 0; row < m_rows; row++){
        for(col = 0; col < m_cols; col++){
            printf("%.2f  ", m[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}


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

	print_matrix(ds.runtime, ds.rows, ds.cols);
	
	alloc_benchmark(&bm);

	// Calculate benchmark metrics (speedup and efficiency)
	calc_speedup(&ds, &bm);
	calc_efficiency(&bm);

	//test
	printf("%f", bm.efficiency[2]);

	exit(0);
}

