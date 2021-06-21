#include "stdlib.h"
#include "time.h"

#include "../inc/errors.h"

#include "../inc/menu.h"

#define ERR_OKAY                        0
#define ERR_NOT_OKAY                    1

int process_return_code(const int rc)
{
    return (OKAY != rc) ? ERR_OKAY : ERR_NOT_OKAY;
}

int main(void)
{
    int rc, grc = ERR_OKAY;

    srand((unsigned) time(NULL));

    rc = menu_run();

    grc = process_return_code(rc);

    return grc;
}
