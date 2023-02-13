#ifndef BMARK_H
#define BMARK_H

#include "commons.h"

void alloc_benchmark(bm_t *bm);
void free_benchmark(bm_t *bm);
void calc_avg_runtime(ds_t *ds, bm_t *bm);
void calc_speedup(bm_t *bm);
void calc_efficiency(bm_t *bm);
void print_benchmark(bm_t *bm);

#endif