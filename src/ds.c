#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/globals.h"


void alloc_ds(ds_t *ds){
	int i;
	ds->procs   = (uint16_t *) calloc(ds->rows, sizeof(uint16_t));
    ds->runtime = (float **)  calloc(ds->rows, sizeof(float *));
	for (i = 0; i < ds->rows; i++)
		ds->runtime[i] = (float *) calloc(ds->cols-1, sizeof(float));
}


void import_data(ds_t *ds, char *path){
	FILE* fp;

	// Open file (read-only)
	fp = fopen(path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror( errno ));
        exit(ER_OPEN);
    }
	
	// Init variables
	char line[BSZ];			// Line buffer
	char del[] = " \t\n";	// Delimiters for splitting
	char *tp; 				// Split string pointer (token)

	ds->rows = ds->cols = 0;
	int total_rows = 0;
	int *skip_bitmap = (int *) malloc(total_rows * sizeof(int)); // Bitmap to skip unusable lines

	/*#########################################*/

	// Check number of columns
	while(fgets(line, BSZ, fp) != NULL) {
		/* Only one line is read to determine number of columns.
		   While loop exists to skip all comments until first usable line. 
		   PREASSUMPTION: all rows have n columns                          */

		// Ignore if comment or empty line
		if (line[0] == '#' || line[0] == '\n')
			continue;

		// Split line into columns and count
		tp = strtok(line, del);
        while(tp) {
            ds->cols++;
            tp = strtok(NULL, tp);
        }

		break; // n columns checked.
	}
	rewind(fp);
	

	// Check number of rows
	while(fgets(line, BSZ, fp) != NULL) { // while ( !feof(fp) )
		skip_bitmap = (int *) realloc(skip_bitmap, ++total_rows * sizeof(int));

		// Ignore if comment or empty line
		if (line[0] == '#' || line[0] == '\n') {
			skip_bitmap[total_rows-1] = 1;
			continue;
		}

		skip_bitmap[total_rows-1] = 0;
		ds->rows++;
	}
	rewind(fp);


	/*#########################################*/
	// Allocate
	alloc_ds(ds);

	// Store into dataset (import)
	int i, j, k, scan;

	k = 0;

	for (i = 0; i < ds->rows; i++){
		
		// Skip if unusable line
		if(skip_bitmap[k++]){
			fgets(line, BSZ, fp);
			i--;
			continue;
		}	

		// Scan file	
		scan = fscanf(fp, "%hu", &ds->procs[i]);
		if (!scan){
			fprintf(stderr, "Error reading file: %s\n", strerror( errno ));
			exit(ER_READ);
		}
			
		for (j = 0; j < ds->cols-1; j++){
			scan = fscanf(fp, "%f", &ds->runtime[i][j]);
			if (!scan){
				fprintf(stderr, "Error reading file: %s\n", strerror( errno ));
				exit(ER_READ);
			}
		}
	}		
	
	fclose(fp);
}


