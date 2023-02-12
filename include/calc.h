#ifndef CALC_H
#define CALC_H

#include "globals.h"

void alloc_benchmark(bm_t *bm);
void calc_speedup(ds_t *ds, bm_t *bm);
void calc_efficiency(bm_t *bm);

#endif