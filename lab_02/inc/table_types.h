#ifndef __TABLE_TYPES_H__

#define __TABLE_TYPES_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define COUNTRY_NAME_LEN                30
#define CAPITAL_NAME_LEN                30

#define MAX_COUNTRY_NUM                 150

/*
#define MAX_MAINLAND_LEN                13
#define MAX_TOURISM_TYPE_LEN            9
#define MAX_EXCURSION_TYPE_LEN          7
#define MAX_SEASON_LEN                  6
#define MAX_SPORT_LEN                   13
*/

#define MAX_MAINLAND_LEN                30
#define MAX_TOURISM_TYPE_LEN            30
#define MAX_EXCURSION_TYPE_LEN          30
#define MAX_SEASON_LEN                  30
#define MAX_SPORT_LEN                   30

struct tourism_excursion_t
{
    uint32_t object_num;
    char excursion_type[MAX_EXCURSION_TYPE_LEN + 1];
};

struct tourism_beach_t
{
    char season[MAX_SEASON_LEN + 1];
    int32_t temp_water;
    int32_t temp_air;
    uint32_t time_flight;
};

struct tourism_sport_t
{
    char sport[MAX_SPORT_LEN + 1];
    uint32_t min_cost;
};

typedef struct
{
    char name[COUNTRY_NAME_LEN + 1];
    uint32_t population;
    char capital[CAPITAL_NAME_LEN + 1];
    char mainland[MAX_MAINLAND_LEN + 1];

    char tourism_type[MAX_TOURISM_TYPE_LEN + 1];
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


enum tourism_type_t { EXCURSION, BEACH, SPORT };

#define TOURISM_TYPE_TO_STR(ENUM)   \
EXCURSION == ENUM ? "Excursion" :   \
BEACH     == ENUM ? "Beach"     :   \
SPORT     == ENUM ? "Sport"     : "Unknown"

#define TOURISM_TYPE_TO_ENUM(STR)   \
!strcmp(STR, "Excursion")   ? 0 :   \
!strcmp(STR, "Beach")       ? 1 :   \
!strcmp(STR, "Sport")       ? 2 : -1


enum excursion_type_t { NATURE, HISTORY, ART };

#define EXCURSION_TYPE_TO_STR(ENUM) \
NATURE  == ENUM ? "Nature"  :       \
HISTORY == ENUM ? "History" :       \
ART     == ENUM ? "Art"     : "Unknown"

#define EXCURSION_TYPE_TO_ENUM(STR) \
!strcmp(STR, "Nature")      ? 0 :   \
!strcmp(STR, "History")     ? 1 :   \
!strcmp(STR, "Art")         ? 2 : -1


enum season_type_t { WINTER, SPRING, SUMMER, AUTUMN };

#define SEASON_TO_STR(ENUM) \
WINTER == ENUM ? "Winter" : \
SPRING == ENUM ? "Spring" : \
SUMMER == ENUM ? "Summer" : \
AUTUMN == ENUM ? "Autumn" : "Unknown"

#define SEASON_TO_ENUM(STR) \
!strcmp(STR, "Winter")      ? 0 :   \
!strcmp(STR, "Spring")      ? 1 :   \
!strcmp(STR, "Summer")      ? 2 :   \
!strcmp(STR, "Autumn")      ? 3 : -1


enum sport_type_t { ALPINE_SKIING, SURFING, CLIMBING };

#define SPORT_TO_STR(ENUM)                      \
ALPINE_SKIING   == ENUM ? "Alpine_skiing"   :   \
SURFING         == ENUM ? "Surfing"         :   \
CLIMBING        == ENUM ? "Climbing"        : "Unknown"

#define SPORT_TO_ENUM(STR) \
!strcmp(STR, "Alpine_skiing")   ? 0 :   \
!strcmp(STR, "Surfing")         ? 1 :   \
!strcmp(STR, "Climbing")        ? 2 : -1


enum mainland_t {AF, NA, AN, EA, SA};

#define MAINLAND_TO_STR(ENUM)   \
AF == ENUM ? "Africa"       :   \
NA == ENUM ? "North_America":   \
AN == ENUM ? "Antarctica"   :   \
EA == ENUM ? "Eurasia"      :   \
SA == ENUM ? "South_America": "Unknown"

#define MAINLAND_TO_ENUM(STR)   \
!strcmp(STR, "Africa")          ? 0 :   \
!strcmp(STR, "North_America")   ? 1 :   \
!strcmp(STR, "Antarctica")      ? 2 :   \
!strcmp(STR, "Eurasia")         ? 3 :   \
!strcmp(STR, "South_America")   ? 4 : -1

#endif // __TABLE_TYPES_H__
