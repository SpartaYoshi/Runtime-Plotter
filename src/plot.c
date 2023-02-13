#include <stdio.h>
#include <stdlib.h>

#include "../include/globals.h"

void plot_graphics(bm_t *bm){
	/* Opens an interface that one can use to send commands as if they were typing into the
	 * gnuplot command line.  
	 * The "-persistent" keeps the plot open even after the C program terminates.
	 */
	FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
	
	// Average runtime
	char * cmdseq[] = {
		"set term png", // export as .png
		"set title 'Average runtime'", 
		"set xlabel 'Processors'",
		"set ylabel 'Execution time (ms)'",
		"set style data lines", // line graph
		"set style line 1 lc rgb '#1197f0' lt 1 lw 3 pt 6 ps 1", // linecolor skyblue, linewidth 2.5, round points, pointsize 2
		"set output 'out/plot_exec.png'",
		"plot 'out/results.dat' using 2:xticlabels(1) t '' with linespoints ls 1"
	};

	// Speedup
	char * cmdseq2[] = {
		"set term png", // export as .png
		"set title 'Speedup'", 
		"set xlabel 'Processors'",
		"set ylabel 'Speedup factor'",
		"set style data lines", // line graph
		"set style line 1 lc rgb '#e8096a' lt 1 lw 3 pt 6 ps 1", // linecolor magenta, linewidth 2.5, round points, pointsize 2
		"set output 'out/plot_su.png'",
		"plot 'out/results.dat' using 3:xticlabels(1) t '' with linespoints ls 1"
	};

	// Efficiency
	char * cmdseq3[] = {
		"set term png", // export as .png
		"set title 'Efficiency'", 
		"set xlabel 'Processors'",
		"set ylabel 'Efficiency factor'",
		"set style data lines", // line graph
		"set style line 1 lc rgb '#d1b70a' lt 1 lw 3 pt 6 ps 1", // linecolor gold, linewidth 2.5, round points, pointsize 2
		"set output 'out/plot_eff.png'",
		"plot 'out/results.dat' using 4:xticlabels(1) t '' with linespoints ls 1"
	};

	int i;
	for (i = 0; i < LENGTH(cmdseq); i++)
		fprintf(gnuplotPipe, "%s \n", cmdseq[i]); //Send commands to gnuplot one by one.
	
	for (i = 0; i < LENGTH(cmdseq2); i++)
		fprintf(gnuplotPipe, "%s \n", cmdseq2[i]); 
	
	for (i = 0; i < LENGTH(cmdseq3); i++)
		fprintf(gnuplotPipe, "%s \n", cmdseq3[i]); 

	pclose(gnuplotPipe);
}