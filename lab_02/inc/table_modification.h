#ifndef __TABLE_MODIFICATION_H__

#define __TABLE_MODIFICATION_H__

#include <inttypes.h>
#include <stdbool.h>

#include "table_types.h"
#include "table_io.h"

#define OKAY                            0
#define MAX_COUNTRY_NUM_EXCEEDED        1

/**
 * @brief Add country to table
 *
 * @return OKAY if success;
 * MAX_COUNTRY_NUM_EXCEEDED if currect country num is max
 */
int table_countries_append(table_countries_t *table, country_t *c);

/**
 * @brief Search country by name
 *
 * @return true and write index if seccuss;
 * false if country not found in table
 */
bool country_found(table_countries_t *table, char *country_name,
size_t *index);

/**
 * Read country name, search and delete first occurrence of readed country
 * name
 */
void table_countries_delete(table_countries_t *table);

#endif // __TABLE_MODIFICATION_H__
