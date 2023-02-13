#include <stdio.h>
#include <stdlib.h>

#include "../include/globals.h"

void plot_graphics(bm_t *bm){
	/* Opens an interface that one can use to send commands as if they were typing into the
     * gnuplot command line.  
     * The "-persistent" keeps the plot open even after the C program terminates.
     */
    FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
	
    char * cmdseq[] = {
		"set term png",
		"set title \"Execution time\"", 
		"set xlabel \"Processors\"",
		"set ylabel \"Runtime (ms)\"",
		"set data style lines",
		"set palette rgb 33,13,10",
		"plot 'out/results.dat'"};

    
    int i;

    for (i=0; i < LENGTH(cmdseq); i++)
    	fprintf(gnuplotPipe, "%s \n", cmdseq[i]); //Send commands to gnuplot one by one.


	pclose(gnuplotPipe);
}