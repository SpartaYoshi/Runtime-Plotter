# Runtime-Plotter
 Program in C made for Parallel Computing Systems (2023). 

## Description
 Reads data of execution time per number of processors, benchmarks performance metrics and plots results in graphs.

 For the plot graphics, _gnuplot_ is used. Results are stored in the **out/** folder, both benchmarks and graphs.

## Inputting data
 A few data samples have been provided for testing the program.
 
 If you want to make your own, please follow the same format. 

 **IMPORTANT NOTES:**
 1. **Use LF, not CRLF, for new lines.**
 2. **Amount of execution times must be equal in all rows (columns of same length).**
 3. **For comments, use # in the beginning. Comments and newlines will be ignored.**

## How to compile
```shell
make clean
make
make plotter
```

## Example
```shell
./runtime-plot samples/enunc.txt
```