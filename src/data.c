#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


#include "../include/commons.h"


void alloc_ds(ds_t *ds){
	int i;
	ds->procs   = (uint16_t *) calloc(ds->rows, sizeof(uint16_t));
    ds->runtime = (float **)  calloc(ds->rows, sizeof(float *));
	for (i = 0; i < ds->rows; i++)
		ds->runtime[i] = (float *) calloc(ds->cols-1, sizeof(float));
}


void free_ds(ds_t *ds){
	int i;
	free(ds->procs);
    free(ds->runtime);
	for (i = 0; i < ds->rows; i++)
		free(ds->runtime[i]);
}


void import_data(ds_t *ds, char *path){
	FILE* fp; // File pointer

	// Open file (read-only)
	fp = fopen(path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror( errno ));
        exit(ER_OPEN);
    }
	
	// Init variables
	char line[BSZ];			    // Line buffer
	char del[] = " \t\n";		// Delimiters for splitting
	char *tp; 				    // Split string pointer (token)

	ds->rows = ds->cols = 0;
	int total_rows = 0;
	int *skip_bitmap = (int *) malloc(total_rows * sizeof(int)); // Bitmap to skip unusable lines

	/*#########################################*/

	// Check number of columns
	while(fgets(line, BSZ, fp) != NULL) {
		/* Only one line is read to determine number of columns.
		   While loop exists to skip all comments until first usable line. 
		   PREASSUMPTION: all rows have n columns                          */

		// Ignore if comment or empty line (+ others)
		if (strchr("#\v\r\n", line[0]) != NULL)
			continue;

		// Split line into columns and count
		tp = strtok(line, del);
        while(tp) {
            ds->cols++;
            tp = strtok(NULL, del);
        }

		break; // n columns checked.
	}
	rewind(fp);
	

	// Check number of rows
	while(fgets(line, BSZ, fp) != NULL) { // while ( !feof(fp) )
		skip_bitmap = (int *) realloc(skip_bitmap, ++total_rows * sizeof(int));

		// Ignore if comment or empty line (+ others)
		if (strchr("#\v\r\n", line[0]) != NULL){
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



void export_data(bm_t *bm){
	FILE *fp; // File pointer
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