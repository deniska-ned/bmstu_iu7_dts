#ifndef __TABLE_MODIFICATION_H__

#define __TABLE_MODIFICATION_H__

#include <inttypes.h>
#include <stdbool.h>

#include "table_types.h"
#include "table_io.h"

#define OKAY                            0

int table_countries_append(table_countries_t *table, country_t *c);

bool country_inde_found(table_countries_t *table, char *country_name,
size_t *index);

int table_countries_delete(table_countries_t *table);

#endif // __TABLE_MODIFICATION_H__
