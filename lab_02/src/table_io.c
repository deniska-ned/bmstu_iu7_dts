#include "../inc/table_io.h"

void goto_newline(FILE *source)
{
    int c;

    while ('\n' != (c = fgetc(source)) && EOF != c)
        ;
}

int read_county(FILE *source, country_t *country)
{
    int rc;
    country_t c;
    int mainland, tourism_type;

    if (EOF == (rc = fscanf(source, "%30s", c.name)))
    {
        return EMPTY_LINE;
    }
    else if (1 != rc)
    {
        LOG_ERROR("country.name failed rc = %d", rc);
        return INCORRECT_DATA;
    }

    if (1 != (rc = fscanf(source, "%"SCNu32, &c.population)))
    {
        LOG_ERROR("country.population failed rc = %d", rc);
        return INCORRECT_DATA;
    }

    if (1 != (rc = fscanf(source, "%30s", c.capital)))
    {
        LOG_ERROR("country.capital failed rc = %d", rc);
        return INCORRECT_DATA;
    }

    if (1 != (rc = fscanf(source, "%d", &mainland)))
    {
        LOG_ERROR("country.mainland failed rc = %d", rc);
        return INCORRECT_DATA;
    }

    if (1 != (rc = fscanf(source, "%d", &tourism_type)))
    {
        LOG_ERROR("country.tourism_type failed rc = %d", rc);
        return INCORRECT_DATA;
    }

    if (mainland < 0 || mainland > 4)
    {
        LOG_ERROR("mainland out of range: %d", mainland);
        return INCORRECT_DATA;
    }
    else if (tourism_type < 0 || tourism_type > 2)
    {
        LOG_ERROR("tourism_type out of range: %d", tourism_type);
        return INCORRECT_DATA;
    }

    strcpy(c.mainland, MAINLAND_TO_STR(mainland));
    strcpy(c.tourism_type, TOURISM_TYPE_TO_STR(tourism_type));

    switch (tourism_type)
    {
        case EXCURSION:
            {
                uint32_t object_num;
                int excursion_type;

                rc = fscanf(source, "%"SCNu32" %d", &object_num,
                &excursion_type);

                if (2 != rc)
                {
                    LOG_ERROR("variant part fscanf_rc = %d; expected 2", rc);
                    return INCORRECT_DATA;
                }
                else if (excursion_type < 0 || excursion_type > 2)
                {
                    LOG_ERROR("incorrect excursion_type %d", excursion_type);
                    return INCORRECT_DATA;
                }

                c.tourism.excursion.object_num = object_num;

                strcpy(c.tourism.excursion.excursion_type,
                EXCURSION_TYPE_TO_STR(excursion_type));

                break;
            }
        case BEACH:
            {
                int season;
                int32_t temp_water, temp_air;
                uint32_t time_flight;

                rc = fscanf(source, "%d %"SCNd32" %"SCNd32" %"SCNu32,
                &season, &temp_water, &temp_air,
                &time_flight);

                if (4 != rc)
                {
                    LOG_ERROR("variant part fscanf_rc = %d; expected 4", rc);
                    return INCORRECT_DATA;
                }
                else if (season < 0 || season > 3)
                {
                    LOG_ERROR("incorrect season %d", season);
                    return INCORRECT_DATA;
                }

                strcpy(c.tourism.beach.season, SEASON_TO_STR(season));
                c.tourism.beach.temp_water = temp_water;
                c.tourism.beach.temp_air = temp_air;
                c.tourism.beach.time_flight = time_flight;

                break;
            }
        case SPORT:
            {
                int sport;
                uint32_t min_cost;

                rc = fscanf(source, "%d %"SCNu32, &sport, &min_cost);

                if (2 != rc)
                {
                    LOG_ERROR("variant part fscanf_rc = %d; expected 2", rc);
                    return INCORRECT_DATA;
                }
                else if (sport < 0 || sport > 2)
                {
                    LOG_ERROR("incorrect sport %d", sport);
                    return INCORRECT_DATA;
                }

                strcpy(c.tourism.sport.sport, SPORT_TO_STR(sport));
                c.tourism.sport.min_cost = min_cost;

                break;
            }
        default:
            LOG_ERROR("Unknown tourism type %d", tourism_type);
            return INCORRECT_DATA;
    }

    *country = c;

    return OKAY;
}

int file_to_table_countries(char *filename, table_countries_t *table)
{
    int rc;

    FILE *f = fopen(filename, "r");

    table->length = 0;

    if (f)
    {
        for (size_t i = 0; i <= MAX_COUNTRY_NUM; ++i)
        {
            rc = read_county(f, &(table->data[i]));

            if (EMPTY_LINE == rc)
            {
                table->length = i;

                break;
            }
            else if (INCORRECT_DATA == rc)
            {
                LOG_ERROR("Incorrect line index: %zu", i);
                return rc;
            }
        }

        LOG_INFO("%zu items read from file", table->length);

        if (EOF == fclose(f))
        {
            LOG_ERROR("%s", "fclose failed");
            return FCLOSE_FAILED;
        }
    }
    else
    {
        LOG_ERROR("File %s not found", filename);
        return FILE_NOT_FOUND;
    }

    return OKAY;
}

int table_countries_to_file(char *filename, table_countries_t table)
{
    FILE *f = fopen(filename, "w");

    if (f)
    {
        for (size_t i = 0; i < table.length; ++i)
        {
            country_t *c = &table.data[i];

            fprintf(f, "%s %"PRIu32" %s %d %d ", c->name, c->population,
            c->capital, MAINLAND_TO_ENUM(c->mainland),
            TOURISM_TYPE_TO_ENUM(c->tourism_type));

            int tourism_type = TOURISM_TYPE_TO_ENUM(c->tourism_type);

            switch (tourism_type)
            {
                case EXCURSION:
                    {
                        struct tourism_excursion_t *excursion;
                        excursion = &(c->tourism.excursion);

                        fprintf(f, "%"PRIu32" %d\n", excursion->object_num,
                        EXCURSION_TYPE_TO_ENUM(excursion->excursion_type));

                        break;
                    }
                case BEACH:
                    {
                        struct tourism_beach_t *beach;
                        beach = &(c->tourism.beach);

                        fprintf(f, "%d %"PRId16" %"PRId16" %"PRIu16"\n",
                        SEASON_TO_ENUM(beach->season), beach->temp_water,
                        beach->temp_air, beach->time_flight);

                        break;
                    }
                case SPORT:
                    {
                        struct tourism_sport_t *sport;
                        sport = &(c->tourism.sport);

                        fprintf(f, "%d %"PRIu32"\n",
                        SPORT_TO_ENUM(sport->sport), sport->min_cost);

                        break;
                    }
            }
        }

        if (EOF == fclose(f))
        {
            LOG_ERROR("%s", "fclose failed");
            return FCLOSE_FAILED;
        }
    }
    else
    {
        LOG_ERROR("File %s not found", filename);
        return FILE_NOT_FOUND;
    }

    LOG_INFO("Table wrote to file %s", filename);
    return OKAY;
}

void gen_table_keys(table_countries_t *table_countries,
table_keys_t *table_keys)
{
    size_t i;
    for (i = 0; i < table_countries->length; ++i)
    {
        table_keys->data[i].src_index = i;
        strcpy(table_keys->data[i].name, table_countries->data[i].name);
    }
    table_keys->length = i;
}

void print_table_countries_row(size_t index, country_t *c)
{
    char *format = "%3zu│%-15s│%10"PRIu32"│%-15s│%-13s│";

    printf(format, index, c->name, c->population, c->capital, c->mainland);

    int tourism_type = TOURISM_TYPE_TO_ENUM(c->tourism_type);

    assert(-1 != tourism_type);

    switch (tourism_type)
    {
        case EXCURSION:
            {
                struct tourism_excursion_t *excursion;
                excursion = &(c->tourism.excursion);

                printf("Экскурсии -> Число объектов: %" PRIu32 "; Тип: %s\n",
                excursion->object_num, excursion->excursion_type);

                break;
            }
        case BEACH:
            {
                struct tourism_beach_t *beach;
                beach = &(c->tourism.beach);

                printf("Пляж -> Сезон: %s; t воды: %"PRId16
                "; t воздуха: %"PRId16"; Время полета: %"PRIu16"\n",
                beach->season,
                beach->temp_water, beach->temp_air, beach->time_flight);

                break;
            }
        case SPORT:
            {
                struct tourism_sport_t *sport;
                sport = &(c->tourism.sport);

                printf("Спорт -> Вид: %s; Минимальная стоимость:"
                " %"PRIu32"\n", sport->sport, sport->min_cost);

                break;
            }
    }
}

void print_table_countries(table_countries_t *table)
{
    if (table->length < 1)
    {
        printf("Пустая таблица\n");
        return;
    }

    printf(TABLE_COUNTRIES_HEADER);

    for (size_t i = 0; i < table->length; ++i)
    {
        country_t *c = &table->data[i];
        
        print_table_countries_row(i, c);
    }
}

void print_table_keys(table_keys_t *table)
{
    printf(TABLE_KEYS_HEADER);

    char *format = "%5zu│%5zu│%s\n";
    for (size_t i = 0; i < table->length; ++i)
    {
        key_name_t *key = &table->data[i];

        printf(format, i, key->src_index, key->name);
    }
}

void print_by_mainland_and_sport(table_countries_t *table)
{
    printf(SEARCH_BY_MAINLAND_AND_SPORT_INTRO);
    printf("> ");

    int mainland, sport;

    if (2 != fscanf(stdin, "%d %d", &mainland, &sport))
    {
        printf(MESS_INCORRECT_INPUT);
        return;

        goto_newline(stdin);
    }
    
    if (mainland < 0 || mainland > 4)
    {
        fprintf(stderr, "Недопустимое значение континента: %d\n", mainland);
        return;
    }
    else if (sport < 0 || sport > 2)
    {
        fprintf(stderr, "Недопустимое значение вида спорта %d\n", sport);
        return;
    }

    goto_newline(stdin);

    bool is_header_printed = false;
    for (size_t i = 0; i < table->length; ++i)
    {
        country_t *c = &table->data[i];

        int c_mainland = MAINLAND_TO_ENUM(c->mainland);
        int c_tourism_type = TOURISM_TYPE_TO_ENUM(c->tourism_type);
        int c_sport = SPORT_TO_ENUM(c->tourism.sport.sport);

        if (c_mainland == mainland && c_tourism_type == SPORT &&
        c_sport == sport)
        {
            if (!is_header_printed)
            {
                printf("\n");
                printf(TABLE_COUNTRIES_HEADER);
                is_header_printed = true;
            }
            print_table_countries_row(i, c);
        }
    }

    if (!is_header_printed)
        printf("\nИскомые страны не найдены\n");
}
