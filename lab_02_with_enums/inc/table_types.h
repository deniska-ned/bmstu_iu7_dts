#ifndef __TABLE_TYPES_H__

#define __TABLE_TYPES_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define COUNTRY_NAME_LEN                10
#define CAPITAL_NAME_LEN                10

#define MAX_COUNTRY_NUM                 100

enum tourism_type_t { EXCURSION, BEACH, SPORT };

enum excursion_type_t { NATURE, HISTORY, ART };
#define EXCURSION_TYPE_TO_STR(ENUM) \
NATURE  == ENUM ? "Nature"  :       \
HISTORY == ENUM ? "History" :       \
ART     == ENUM ? "Art"     : "Unknown"

enum season_type_t { WINTER, SPRING, SUMMER, AUTUMN };
#define SEASON_TO_STR(ENUM) \
WINTER == ENUM ? "Winter" : \
SPRING == ENUM ? "Spring" : \
SUMMER == ENUM ? "Summer" : \
AUTUMN == ENUM ? "Autumn" : "Unknown"

enum sport_type_t { ALPINE_SKIING, SURFING, CLIMBING };
#define SPORT_TO_STR(ENUM)                      \
ALPINE_SKIING   == ENUM ? "Alpine skiing"   :   \
SURFING         == ENUM ? "Surfing"         :   \
CLIMBING        == ENUM ? "Climbing"        : "Unknown"

struct tourism_excursion_t
{
    uint32_t object_num;
    enum excursion_type_t excursion_type;
};

struct tourism_beach_t
{
    enum season_type_t season;
    int32_t temp_water;
    int32_t temp_air;
    uint32_t time_flight;
};

struct tourism_sport_t
{
    enum sport_type_t sport;
    uint32_t min_cost;
};

enum mainland_t {AF, NA, AN, EA, SA};
#define MAINLAND_TO_STR(ENUM)   \
AF == ENUM ? "Africa"       :   \
NA == ENUM ? "North America":   \
AN == ENUM ? "Antarctica"   :   \
EA == ENUM ? "Eurasia"      :   \
SA == ENUM ? "South America": "Unknown"

typedef struct
{
    char name[COUNTRY_NAME_LEN + 1];
    uint32_t population;
    char capital[CAPITAL_NAME_LEN + 1];
    enum mainland_t mainland;

    enum tourism_type_t tourism_type;
    union tourism
    {
        struct tourism_excursion_t excursion;
        struct tourism_beach_t beach;
        struct tourism_sport_t sport;
    } tourism;
} country_t;

typedef struct
{
    country_t data[MAX_COUNTRY_NUM];
    size_t length;
} table_countries_t;

typedef struct 
{
    size_t src_index;
    char name[COUNTRY_NAME_LEN + 1];
} key_name_t;

typedef struct
{
    key_name_t data[MAX_COUNTRY_NUM];
    size_t length;
} table_keys_t;

#endif // __TABLE_TYPES_H__
