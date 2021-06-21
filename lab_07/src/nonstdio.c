#include "../inc/nonstdio.h"

void goto_newline(FILE *source)
{
    int c;
    while ('\n' != (c = fgetc(source)) && EOF != c)
        ;
}
