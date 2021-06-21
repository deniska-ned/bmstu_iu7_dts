#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define MESS_MENU_MAIN \
"\n" \
"Главное меню:\n" \
"1. Работать с двоичным деревом поиска (ДДП)\n" \
"2. Работать со сбалансированным деревом (АВЛ)\n" \
"3. Работать с хеш таблицей\n" \
"4. Работать в файлом\n" \
"5. Вывод статистики\n" \
"\n" \
"0. Выйти\n"

#define MENU_MAIN_TREE                  1
#define MENU_MAIN_BTREE                 2
#define MENU_MAIN_HASH                  3
#define MENU_MAIN_FILE                  4
#define MENU_MAIN_STAT                  5
#define MENU_MAIN_EXIT                  0

#define MESS_MENU_HEADER_TREE \
"\n"                          \
"Меню работы с ДДП: \n"

#define MESS_MENU_HEADER_BTREE \
"\n"                           \
"Меню работы с АВЛ: \n"

#define MESS_MENU_HEADER_HASH_TABLE \
"\n"                                \
"Меню работы с хеш-таблицей: \n"

#define MESS_MENU_HEADER_FILE \
"\n"                          \
"Меню работы с файлом: \n"

#define MESS_MENU_FILE MESS_MENU_TREE

#define MESS_MENU_TREE \
"1. Добавить из файла\n" \
"2. Добавить вручную\n" \
"3. Удалить\n" \
"4. Найти\n" \
"5. Вывести\n" \
"\n" \
"0. Выйти\n"

#define MESS_MENU_HASH \
"1. Добавить из файла\n" \
"2. Добавить вручную\n" \
"3. Удалить\n" \
"4. Найти\n" \
"5. Вывести\n" \
"6. Посчитать среднее число сравнений\n" \
"\n" \
"0. Выход\n"

#define MENU_SECONDARY_ADD_FROM_FILE    1
#define MENU_SECONDARY_ADD              2
#define MENU_SECONDARY_DEL              3
#define MENU_SECONDARY_FIND             4
#define MENU_SECONDARY_PRINT            5
#define MENU_SECONDATY_AVG_CMP          6
#define MENU_SECONDARY_EXIT             0

#define MESS_MENU_CHOICE \
"\n" \
"Ваш выбор: "

#define MESS_INCORRECT_INPUT            "Некорректный ввод\n"

#define MESS_INPUT_NUM                  "Введите число: "

#define MESS_INCORRECT_INPUT            "Некорректный ввод\n"

#define MESS_EXIT                       "Выход\n"

#define MESS_NUM_NOT_FOUND              "Число не найдено\n"

#define MESS_FILE_READING_ERROR         "Ошибка чтения файла\n"

#define MESS_INPUT_FILENAME             "Введите название файла: "

#define MESS_NUM_FROM_FILE_READED       "Значения из файла прочитаны\n"

#define MESS_INPUT_TABLE_LEN            "Введите длину хеш-таблицы: "

#define MESS_INPUT_MAX_CMP              "Введите максимальное число сравнений: "

#define MESS_UNABLE_CREATE_TABLE        "Невозможно создать таблицу\n"

#define MESS_TABLE_OVERFLOW             "Таблица переполнена\n"

#define MESS_FILE_CANNOT_BE_OPENED      "Файл не найден\n"

#define MESS_ALLOCATION_FAILED          "Ошибка выделения памяти\n"

#define MESS_MENU_DATA_TYPE \
"Выберите тип исходных данных: \n" \
"\n" \
"1. Не отсортированные\n" \
"2. Отсортированные\n"

#define MESS_INPUT_NUM_COUNT_RANGE \
"Введите минимальное число элементов, максимальное и шаг: "

#define MESS_ERROR "Ошибка\n"

#endif // __MESSAGES_H__
