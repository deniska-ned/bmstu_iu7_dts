#ifndef __MENU_H__

#define __MENU_H__

#include <stdio.h>
#include <stdlib.h>

#include "../inc/table_types.h"
#include "../inc/table_io.h"
#include "../inc/errors.h"
#include "../inc/sort.h"
#include "../inc/table_modification.h"
#include "../inc/messages.h"
#include "../inc/statistics.h"

/**
 * @brief Show menu and exexute selected func
 */
int run_menu(table_countries_t *table_countries);

#endif // __MENU_H__
