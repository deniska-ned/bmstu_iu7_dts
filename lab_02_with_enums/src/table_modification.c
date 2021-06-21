#include "../inc/table_modification.h"

int table_countries_append(table_countries_t *table, country_t *country)
{
    if (MAX_COUNTRY_NUM == table->length)
    {
        printf("There is the max country number\n");
        return OKAY;
    }

    size_t len = table->length;

    table->data[len] = *country;
    table->length++;

    return OKAY;
}

bool country_inde_found(table_countries_t *table, char *country_name,
size_t *index)
{
    for (size_t i = 0; i < table->length; ++i)
    {
        if (!strcmp(country_name, table->data[i].name))
        {
            *index = i;
            return true;
        }
    }

    return false;
}

int table_countries_delete(table_countries_t *table)
{
    char country_name[COUNTRY_NAME_LEN + 1];

    printf("Enter country name for delete: ");
    scanf("%10s", country_name);

    goto_newline(stdin);

    size_t country_i;

    if (country_inde_found(table, country_name, &country_i))
    {
        for (size_t i = country_i; i < table->length - 1; ++i)
            table->data[i] = table->data[i + 1];

        table->length--;

        printf("\n%s removed from table\n", country_name);
    }
    else
    {
        printf("\n%s not found in table\n", country_name);
    }

    return OKAY;
}
