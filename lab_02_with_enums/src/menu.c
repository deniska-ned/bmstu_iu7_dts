#include "../inc/menu.h"

int run_menu(table_countries_t *table_countries)
{
    int rc, grc;
    int menu_selection;

    table_keys_t table_keys;
    table_countries_t s_table_countries;

    gen_table_keys(table_countries, &table_keys);
    qsort(table_keys.data, table_keys.length, sizeof(key_name_t), &comp_keys);

    do
    {
        printf("\n"MENU_STR);
        printf("\nВaш выбор: ");

        if (1 != (rc = scanf("%d", &menu_selection)))
        {
            fprintf(stderr, "\nNot a number entered\n");
            LOG_ERROR("scanf rc = %d", rc);
            fprintf(stderr, "Enter 0 to exit\n");

            while ('\n' != getchar())
                ;

            continue;
        }
        printf("\n");

        switch (menu_selection)
        {
            case 0:
                grc = 256;
                printf("See you later\n");
                break;
            case 1:
                {
                    country_t country;

                    printf(COUNTRY_INPUT_INTRO);
                    printf("\n> ");
                    rc = read_county(stdin, &country);

                    if (OKAY != rc)
                    {
                        fprintf(stderr, "Incorrect data\n");
                        continue;
                    }
                    printf(TABLE_COUNTRIES_HEADER);
                    print_table_countries_row(0, &country);

                    printf("Added");

                    table_countries_append(table_countries, &country);

                    break;
                }
            case 2:
                table_countries_delete(table_countries);

                gen_table_keys(table_countries, &table_keys);

                qsort(table_keys.data, table_keys.length,
                sizeof(key_name_t), &comp_keys);
                break;
            case 3:
                s_table_countries = *table_countries;

                qsort(s_table_countries.data, s_table_countries.length,
                sizeof(country_t), &comp_countries);

                print_table_countries(&s_table_countries);
                break;
            case 4:
                print_table_countries(table_countries);
                break;
            case 5:
                print_table_keys(&table_keys);
                break;
            case 6:
                show_ticks_statistics(table_countries);
                break;
            case -6:
                gen_table_keys(table_countries, &table_keys);
                show_clock_statistics(table_countries, &table_keys);
                break;
            case 7:
                print_by_mainland_and_sport(table_countries);

                break;
            default:
                LOG_ERROR("Unknown menu case %d", menu_selection);
                printf(MESS_UNKNOWN_MENU_SELECTION);
                printf("Enter 0 to exit\n");
        }
    } while (ERR_OKAY == grc);

    return grc;
}
