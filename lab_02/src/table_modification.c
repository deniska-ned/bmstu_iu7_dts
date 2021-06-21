#include "../inc/table_modification.h"

int table_countries_append(table_countries_t *table, country_t *country)
{
    if (MAX_COUNTRY_NUM == table->length)
    {
        printf("В таблице максимальное число стран\n");
        return MAX_COUNTRY_NUM_EXCEEDED;
    }

    size_t len = table->length;

    table->data[len] = *country;
    table->length++;

    return OKAY;
}

bool country_found(table_countries_t *table, char *country_name,
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

void table_countries_delete(table_countries_t *table)
{
    char country_name[COUNTRY_NAME_LEN + 1];

    printf("Введите название страны для удаления: ");
    scanf("%10s", country_name);

    goto_newline(stdin);

    size_t country_i;

    if (country_found(table, country_name, &country_i))
    {
        for (size_t i = country_i; i < table->length - 1; ++i)
            table->data[i] = table->data[i + 1];

        table->length--;

        printf("\n%s удалена из таблицы\n", country_name);
    }
    else
    {
        printf("\n%s не найдена\n", country_name);
    }
}
