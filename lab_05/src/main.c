#include <stdio.h>

#include "../inc/random.h"
#include "../inc/menu.h"

int main(void)
{
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    random_init();

    run_menu();
}
