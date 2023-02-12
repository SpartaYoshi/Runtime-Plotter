#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/globals.h"


void alloc_ds(ds_t *ds){
	int i;
	ds->procs   = (uint8_t *) calloc(ds->rows, sizeof(uint8_t));
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
		
		// Ignore if comment or empty line
		if (line[0] == '#' || line[0] == '\n')
			continue;

		ds->rows++;
	}
	rewind(fp);


	/*#########################################*/
	// Allocate
	alloc_ds(ds);

	// Import data
	int i, j, scan;
	while(fgets(line, BSZ, fp) != NULL) {

		// Ignore if comment or empty line
		if (line[0] == '#' || line[0] == '\n')
			continue;

		// Store into dataset
		for (i = 0; i < ds->rows; i++){
			scan = fscanf(fp, "%hhu", &ds->procs[i]);
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
	}

	return;
}


