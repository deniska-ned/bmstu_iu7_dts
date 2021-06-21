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

    /*
    char *format = "%10s %" SCNu32 " %10s %d %d";

    rc = fscanf(source, format,
            c.name, &c.population, c.capital, &mainland, &tourism_type);

    LOG_INFO("Static part of country_t read, rc == %d", rc);

    */

    if (EOF == (rc = fscanf(source, "%10s", c.name)))
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

    if (1 != (rc = fscanf(source, "%10s", c.capital)))
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

    c.mainland = mainland;
    c.tourism_type = tourism_type;

    switch (tourism_type)
    {
        case EXCURSION:
            {
                char *format = "%"SCNu32" %d";

                uint32_t object_num;
                int excursion_type;

                rc = fscanf(source, format, &object_num, &excursion_type);

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
                c.tourism.excursion.excursion_type = excursion_type;

                break;
            }
        case BEACH:
            {
                char *format = "%d %" SCNd32 " %" SCNd32 " %" SCNu32;

                int season;
                int16_t temp_water, temp_air;
                uint16_t time_flight;

                rc = fscanf(source, format, &season, &temp_water, &temp_air,
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

                c.tourism.beach.season = season;
                c.tourism.beach.temp_water = temp_water;
                c.tourism.beach.temp_air = temp_air;
                c.tourism.beach.time_flight = time_flight;

                break;
            }
        case SPORT:
            {
                char *format = "%d %" SCNu32;

                int sport;
                uint32_t min_cost;

                rc = fscanf(source, format, &sport, &min_cost);

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

                c.tourism.sport.sport = sport;
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
        char *format = "%s %"PRIu32" %s %d %d ";

        for (size_t i = 0; i < table.length; ++i)
        {
            country_t *c = &table.data[i];

            fprintf(f, format, c->name, c->population, c->capital, c->mainland,
            c->tourism_type);

            int tourism_type = c->tourism_type;

            switch (tourism_type)
            {
                case EXCURSION:
                    {
                        struct tourism_excursion_t *excursion;
                        excursion = &(c->tourism.excursion);

                        char *format = "%" PRId64 " %d\n";

                        fprintf(f, format, excursion->object_num,
                        excursion->excursion_type);

                        break;
                    }
                case BEACH:
                    {
                        struct tourism_beach_t *beach;
                        beach = &(c->tourism.beach);

                        char *format = "%d %"PRId16" %"PRId16" %"PRIu16"\n";

                        fprintf(f, format, beach->season, beach->temp_water,
                        beach->temp_air, beach->time_flight);

                        break;
                    }
                case SPORT:
                    {
                        struct tourism_sport_t *sport;
                        sport = &(c->tourism.sport);

                        char *format = "%d %"PRIu32"\n";

                        fprintf(f, format, sport->sport, sport->min_cost);

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
    char *format = "%3zu│%-10s│%10"PRIu32"│%-10s│%-13s│";

    printf(format, index, c->name, c->population, c->capital,
            MAINLAND_TO_STR(c->mainland));

    int tourism_type = c->tourism_type;

    switch (tourism_type)
    {
        case EXCURSION:
            {
                struct tourism_excursion_t *excursion;
                excursion = &(c->tourism.excursion);

                char *format = "EXCURSION -> Object num: %" PRId64 "; "
                "Type: %s\n";

                printf(format, excursion->object_num,
                EXCURSION_TYPE_TO_STR(excursion->excursion_type));

                break;
            }
        case BEACH:
            {
                struct tourism_beach_t *beach;
                beach = &(c->tourism.beach);

                char *format = "BEACH -> Season: %s; Water temp: %"PRId16
                "; Air temp: %"PRId16"; Time to: %"PRIu16"\n";

                printf(format, SEASON_TO_STR(beach->season),
                beach->temp_water, beach->temp_air, beach->time_flight);

                break;
            }
        case SPORT:
            {
                struct tourism_sport_t *sport;
                sport = &(c->tourism.sport);

                char *format = "SPORT -> Type: %s; Min cost: %"PRIu32"\n";

                printf(format, SPORT_TO_STR(sport->sport),
                sport->min_cost);

                break;
            }
    }
}

void print_table_countries(table_countries_t *table)
{
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
        printf("Incorrect input\n");
        return;
    }
    
    if (mainland < 0 || mainland > 4)
    {
        fprintf(stderr, "mainland out of range: %d\n", mainland);
        return;
    }
    else if (sport < 0 || sport > 2)
    {
        fprintf(stderr, "incorrect sport %d\n", sport);
        return;
    }

    goto_newline(stdin);

    bool is_header_printed = false;
    for (size_t i = 0; i < table->length; ++i)
    {
        country_t *c = &table->data[i];
        if (c->mainland == (unsigned) mainland && c->tourism_type == SPORT &&
        c->tourism.sport.sport == (unsigned) sport)
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
        printf("\nCountries not found\n");
}
