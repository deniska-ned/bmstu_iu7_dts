#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define MESS_MENU \
"Меню:\n" \
"1. Добавить из файла\n" \
"2. Добавить вручную\n" \
"3. Вывести граф\n" \
"4. Найти нужные вершины\n" \
"\n" \
"0. Выход\n"

#define MESS_MENU_CHOICE \
"\n" \
"Ваш выбор: "

#define MENU_ADD_FROM_FILE              1
#define MENU_ADD_MANUALLY               2
#define MENU_GRAPH_OUTPUT               3
#define MENU_SEARCH                     4
#define MENU_EXIT                       0

#define MESS_INCORRECT_INPUT            "Некорректный ввод\n"

#define MESS_EXIT                       "Выход\n"

#define MESS_TODO                       "Not implemented yet\n"

#define MESS_ALLOCATION_FAILED          "Ошибка выделения памяти\n"

#define MESS_FILE_CANNOT_BE_OPENED      "Файл не найден\n"

#define MESS_FILE_READING_ERROR         "Ошибка чтения файла\n"

#define MESS_INPUT_FILENAME             "Введите название файла: "

#define MESS_FILE_READING_SUCCESS       "Данные из файла успешно прочитаны\n"

#define MESS_ADDING_SUCCESS             "Значение успешно добавлено\n"

#endif // __MESSAGES_H__
