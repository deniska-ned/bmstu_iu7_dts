#include "../inc/nonstdio.h"

void goto_newline(FILE *source)
{
    int c;
    while ('\n' != (c = fgetc(source)) && EOF != c)
        ;
}

int read_word(FILE *source, char *str)
{
    int rc, c;
    
    rc = fscanf(source, "%" MAX_WORD_LEN_SCANF "s", str);

    if (1 != rc)
    {
        LOG_ERROR("fcanf return %d", rc);

        return EOF;
    }

    int fgetc_count = 0;

    do
    {
        c = fgetc(source);
        ++fgetc_count;
    }
    while ('\n' != c && ' ' != c && EOF != c);

    if (EOF != c)
        ungetc(c, source);

    return (1 == fgetc_count) ? OKAY : MAX_WORD_LEN_EXCEEDED;
}
