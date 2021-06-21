#include <stdio.h>
#include <stdlib.h>

#include "../inc/menu.h"
#include "../inc/table_types.h"
#include "../inc/table_io.h"
#include "../inc/errors.h"
#include "../inc/sort.h"
#include "../inc/table_modification.h"
#include "../inc/messages.h"

#define FILENAME "database.txt"

int process_rc(char *func_name, const int rc)
{
    if (!strcmp("main", func_name))
        switch (rc)
        {
            case OKAY:
                return OKAY;
            // case UNKNOWN_MENU_SELECTION:
            //     fprintf(stderr, MESS_UNKNOWN_MENU_SELECTION);
            //     return ERR_UNKNOWN_MENU_SELECTION;
            default:
                fprintf(stderr, MESS_UNKNOWN);
                return ERR_UNKNOWN;
        }

    if (!strcmp("file_to_table_countries", func_name))
        switch (rc)
        {
            case OKAY:
                return ERR_OKAY;
            case INCORRECT_DATA:
                fprintf(stderr, MESS_INCORRECT_DATA);
                return ERR_INCORRECT_DATA;
            case FCLOSE_FAILED:
                fprintf(stderr, MESS_FCLOSE_FAILED);
                return ERR_FCLOSE_FAILED;
            case FILE_NOT_FOUND:
                fprintf(stderr, MESS_FILE_NOT_FOUND);
                return ERR_FILE_NOT_FOUND;
            default:
                fprintf(stderr, MESS_UNKNOWN);
                return ERR_UNKNOWN;
        }

    fprintf(stderr, MESS_UNKNOWN_FUNCTION);
    return ERR_UNKNOWN_FUNCTION;
}

int main(void)
{ 
    int rc, grc = ERR_OKAY;

    table_countries_t table_countries;

    if (OKAY != (rc = file_to_table_countries(FILENAME, &table_countries)))
        return process_rc("file_to_table_countries", rc);

    run_menu(&table_countries);
    
    if (OKAY != (rc = table_countries_to_file(FILENAME, table_countries)))
        grc = process_rc("table_countries_to_file", rc);

    return grc;
}
