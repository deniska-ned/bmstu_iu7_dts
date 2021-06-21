# Отчет по Лабораторной работе №2 "Записи с вариантами, обработка таблиц"

Студент: **Недолужко Денис**

Группа: **ИУ7-33Б**

Год: 2020

## Описание условия задачи

Создать таблицу, содержащую не менее 40-ка записей (тип –
запись с вариантами (объединениями)). Упорядочить данные
в ней по возрастанию ключей, двумя алгоритмами
сортировки, где ключ – любое невариантное поле (по выбору
программиста), используя: а) саму таблицу, б) массив ключей.
(Возможность добавления и удаления записей в ручном
режиме обязательна). Осуществить поиск информации по
варианту.

Ввести список стран, содержащий название страны, количество
жителей, столицу, материк, основной вид туризма (экскурсионный -
количество объектов, основной вид (природа, история, искусство);
пляжный – основной сезон, температура воздуха и воды, время
полета до страны; спортивный – вид спорта (горные лыжи,
серфинг, восхождения), минимальная стоимость отдыха). Вывести
список стран на выбранном материке, где можно заняться
указанным видом спорта.

## Техническое задание

### Входные данных

Пункт меню (от 0 до 7), параменты добавляемой и удаляемой информации.

### Выходные данные

* Таблица стран (отсортированная и неотсортированная)
* Таблица ключей
* Результаты сравнения сортировок таблицы стран и таблицы ключей
* Страны на введенном материке с искомым типом спорта

### Способ обращения к программе

Запускается в терминале командой `./app.exe` в папке с программой.

### Описание возможных аварийных ситуаций и ошибок пользователя

1. Некорректные данные во входном файле. Сообщение `INCORRECT FILE`
1. Некорректные данные при вводе пользователя. Сообщение `INCORRECT DATA`
1. Выбор несуществующего пунтка меню `Unknown menu case. Enter 0 to exit`

## Описание внутренних структур данных

```C
#define COUNTRY_NAME_LEN                30
#define CAPITAL_NAME_LEN                30

#define MAX_COUNTRY_NUM                 100

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

enum excursion_type_t { NATURE, HISTORY, ART };

enum season_type_t { WINTER, SPRING, SUMMER, AUTUMN };

enum sport_type_t { ALPINE_SKIING, SURFING, CLIMBING };

enum mainland_t {AF, NA, AN, EA, SA};
```

### Функции программы

```C
/**
 * @brief Show menu and exexute selected func
 */
int run_menu(table_countries_t *table_countries);

/**
 * Compare two country table row func for sort func
 *
 * @return A negative integer value if the first argument is less than the
 * second, a positive integer value if the first argument is greater than the
 * second and zero if the arguments are equivalent
 */
int comp_countries(const void *ptr_country_1, const void *ptr_country_2);

/**
 * Compare two keys func for sort func
 *
 * @return A negative integer value if the first argument is less than the
 * second, a positive integer value if the first argument is greater than the
 * second and zero if the arguments are equivalent
 */
int comp_keys(const void *ptr_key_1, const void *ptr_key_2);

/**
 * Selection sort
 */
void selection_sort(void *ptr, size_t count, size_t size,
int (*comp)(const void *, const void *));

/**
 * @brief Calculate and show sort time statiscits for country and keys tables
 * for quick sort and selection sort
 */
void show_ticks_statistics(table_countries_t *table_countries);

/**
 * @brief Read symbols until '\\n' or EOF encountered
 */
void goto_newline(FILE *source);

/**
 * @brief Read a line to country_t from file f
 *
 * @return OKAY if not errer;
 * EMPTY_LINE if not data readed from line;
 * INCORRECT_FILE if file data cannot be pass to country_t
 */
int read_county(FILE *f, country_t *country);

/**
 * @brief Read data from file to table
 *
 * @return OKAY if no error;
 * INCORRECT_FILE if incorrect file;
 * FCLOSE_FAILED if fclose failed;
 * FILE_NOT_FOUND if fopen failed;
 */
int file_to_table_countries(char *filename, table_countries_t *table);

/**
 * @brief Write data from country table ro file
 *
 * @return OKAY if no error;
 * FCLOSE_FAILED if fclose failed;
 * FILE_NOT_FOUND if fopen failed;
 */
int table_countries_to_file(char *filename, table_countries_t table);

/**
 * @brief Generate key table from country table
 */
void gen_table_keys(table_countries_t *table_countries,
table_keys_t *table_keys);

/**
 * @brief Print 1 row from county table
 */
void print_table_countries_row(size_t index, country_t *c);

/**
 * @brief Print county table
 */
void print_table_countries(table_countries_t *table);

/**
 * @brief print key table
 */
void print_table_keys(table_keys_t *table);

/**
 * Read mainland and sport type and search countries with this params
 */
void print_by_mainland_and_sport(table_countries_t *table);

/**
 * @brief Add country to table
 *
 * @return OKAY if success;
 * MAX_COUNTRY_NUM_EXCEEDED if currect country num is max
 */
int table_countries_append(table_countries_t *table, country_t *c);

/**
 * @brief Search country by name
 *
 * @return true and write index if seccuss;
 * false if country not found in table
 */
bool country_found(table_countries_t *table, char *country_name,
size_t *index);

/**
 * Read country name, search and delete first occurrence of readed country
 * name
 */
void table_countries_delete(table_countries_t *table);

/**
 * @return Return time stamp counter
 */
uint64_t tick(void);
```

## Набор тестов

### Тесты главного меню

|Входные данные|Выходные данные|
|-|-|
|0|Вывод сообщение "Выход" и выход|
|1|Запуск алгоритма добавления строки|
|10|Вывод "Неизвестный пункт меню.</br>Введите 0 чтобы выйти"|
|c|Вывод "Введено не число</br>Введите 0 чтобы выйти"|

### Тесты добавления страны

|Входыне данные|Выходные данные|
|-|-|
|Russia 146748590 Moscow 3 0 144550 1|Вывод сообщения об добавлении страны|
|f f|Вывод сообщения "Некорретный данные"|

### Тесты удаления страны

|Входыне данные|Выходные данные|
|-|-|
|Название страны из таблице|Сообщение об удалении страны|
|Название страны не из таблице|Сообщение об неудалении страны|

### Тесты для поска стран по материку и виду спорта

|Входыне данные|Выходные данные|
|-|-|
|Данные для существущих стран|Вывод таблицы с данными|
|Данные для несуществуюищх стран|Сообщение "Искомые страны не найдены"|

## Замеры времени и памяти

### 20 стран

|                         |Быстрая сортировка|Сортировка выбором|
|-------------------------|------------------|------------------|
|Сортировка таблицы стран |             4149 |            27354 |
|Создание таблицы ключей  |              364 |              376 |
|Сортировка таблицы ключей| (-20.29%)   3307 | (-59.65%)  11038 |

Таблица стран: 17608 Б
Таблица стран с ключами: 4008 Б (22.76%)

### 140 стран

|                         |Быстрая сортировка|Сортировка выбором|
|-------------------------|------------------|------------------|
|Сортировка таблицы стран |            42036 |           477054 |
|Создание таблицы ключей  |             1565 |             1766 |
|Сортировка таблицы ключей| (-18.64%)  34201 | (-34.11%) 314335 |

Таблица стран: 26408 Б
Таблица стран с ключами: 6008 Б (22.75%)

## Вывод

Таблица ключей, введенная нами для ускорения процесса сортировки, дала
выигрыш по времени в 20-60% при потерях в памяти в 23%.
Таким образом, имея большую таблицу записей, в которой с какой-либо
периодичностью требуется сортировка по какому-либо полю, рационально
ввести массив ключей.

## Контрольные вопросы

1. Как выделяется память под вариантную часть записи?\
Память выделяется по самому длинному вариантному полю.
2. Что будет, если в вариантную часть ввести данные, несоответствующим образом?\
Неизвестно
3. Кто должен следить за правильностью выполнения операций с вариантной частью
записи?\
Программист
4. Что представляет собой таблица ключей, зачем она нужна?
Таблица ключей представляет из себя некую структуру, содержащую индекс и
значение какого-либо выбранного поля таблицы. Она нужна для реализации более
эффективного по времени выполнения перемещения перемещений.
5. В каких случаях эффективнее обрабатывать данные в самой таблице, а когда -
использовать таблицу ключей?\
При исходной таблице имеющей большой размер каждой строки эффективнеее
использовать таблицу ключей, иначе - использовать исходную таблицу
6. Какие способы сортировки предпочтительнее для обработки таблиц и почему?\
Для обработки таблиц предпочтительнее использовать устойчивые сортировки, чтобы
не менять относительный порядок элементов при одинаковом значении поля, по
которому производится сортивровка.
