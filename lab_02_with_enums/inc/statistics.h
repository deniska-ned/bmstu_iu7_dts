#ifndef __STATICTICS_H__

#define __STATICTICS_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "table_io.h"
#include "timer.h"
#include "sort.h"
#include "messages.h"

#define RUN_NUM                         10000

#define SORT_NUM                        2
#define CONTENT_TYPE_NUM                3

void show_ticks_statistics(table_countries_t *table_countries);

void show_clock_statistics(table_countries_t *table_countries,
table_keys_t *table_keys);

#endif // __STATICTICS_H__
