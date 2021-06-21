#ifndef __STATISTICS_H__
#define __STATISTICS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "elem.h"
#include "tree_classic.h"
#include "tree_balance.h"
#include "hash_table.h"
#include "file.h"
#include "messages.h"
#include "mymath.h"
#include "timer.h"
#include "myrandom.h"

#define FILE_NAME "data_for_stat_count.txt"

#define ITERATION_COUNT 2

int statistics_show();

#endif // __STATISTICS_H__
