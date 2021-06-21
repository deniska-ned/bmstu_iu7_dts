#ifndef __ERRORS_H__

#define __ERRORS_H__

#define ERR_OKAY                        0
#define ERR_INCORRECT_DATA              1
#define ERR_FILE_NOT_FOUND              2
#define ERR_UNKNOWN_MENU_SELECTION      252
#define ERR_FCLOSE_FAILED               253
#define ERR_UNKNOWN_FUNCTION            254
#define ERR_UNKNOWN                     255

#define MESS_INCORRECT_DATA             "Некорректные данные\n"
#define MESS_FILE_NOT_FOUND             "Файл не найден\n"
#define MESS_UNKNOWN_MENU_SELECTION     "Неизвестный пункт меню\n"
#define MESS_FCLOSE_FAILED              "Ошибка fclose\n"
#define MESS_UNKNOWN_FUNCTION           "Неизвестная функция\n"
#define MESS_UNKNOWN                    "Неизветсная ошибка\n"

#endif // __ERRORS_H__
