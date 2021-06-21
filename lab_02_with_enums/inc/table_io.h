#ifndef __TABLE_IO_H__

#define __TABLE_IO_H__

#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>

#include "macrologger.h"

#include "table_types.h"
#include "messages.h"

#define OKAY                            0
#define FILE_NOT_FOUND                  1
#define INCORRECT_DATA                  2
#define EMPTY_LINE                      3
#define FCLOSE_FAILED                   4

void goto_newline(FILE *source);

/**
 * @brief Read a line to country_t from file f
 *
 * @return OKAY if not errer;
 * EMPTY_LINE if not data readed from line;
 * INCORRECT_FILE if file data cannot be pass to country_t
 */
int read_county(FILE *f, country_t *country);

/**
 * @brief Read data from file to table
 *
 * @return OKAY if no error;
 * INCORRECT_FILE if incorrect file;
 * FCLOSE_FAILED if fclose failed;
 * FILE_NOT_FOUND if fopen failed;
 */
int file_to_table_countries(char *filename, table_countries_t *table);

int table_countries_to_file(char *filename, table_countries_t table);

void gen_table_keys(table_countries_t *table_countries,
table_keys_t *table_keys);

void print_table_countries_row(size_t index, country_t *c);

void print_table_countries(table_countries_t *table);

void print_table_keys(table_keys_t *table);

void print_by_mainland_and_sport(table_countries_t *table);

#endif // __TABLE_IO_H__
