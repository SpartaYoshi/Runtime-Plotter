#ifndef DS_H
#define DS_H

#include "commons.h"

void import_data(ds_t *ds, char *path);
void export_data(bm_t *bm);
void free_ds(ds_t *ds);

#endif