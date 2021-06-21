#ifndef __MENU_H__
#define __MENU_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/messages.h"

#include "../inc/tree_classic.h"
#include "../inc/tree_balance.h"
#include "../inc/hash_table.h"
#include "../inc/statistics.h"

#include "../inc/nonstdio.h"
#include "../inc/mymath.h"

#define WORK_WITH_FILE_FILENAME "buffer.txt"
#define GV_PATH "dot_files/tree.gv"

int menu_start(void);

#endif // __MENU_H__
