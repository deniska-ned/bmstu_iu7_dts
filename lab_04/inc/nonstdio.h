#ifndef __NONSTDIO_H__

#define __NONSTDIO_H__

#include <stdio.h>

#include "word_info.h"
#include "macrologger.h"

void goto_newline(FILE *source);

#define OKAY                            0
#define MAX_WORD_LEN_EXCEEDED           1
/**
 * @return OKAY if success;
 * EOF if all words readed;
 * MAX_WORD_LEN_EXCEEDED if max word len exceeded;
 */
int read_word(FILE *source, char *str);

#endif // __NONSTDIO_H__
