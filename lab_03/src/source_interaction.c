#include "../inc/source_interaction.h"

int goto_newline(FILE *source)
{
    int c;

    while ('\n' != (c = fgetc(source)) && EOF != c)
        ;

    return c;
}
