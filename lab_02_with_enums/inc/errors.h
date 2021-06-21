#ifndef __ERRORS_H__

#define __ERRORS_H__

#define ERR_OKAY                        0
#define ERR_INCORRECT_DATA              1
#define ERR_FILE_NOT_FOUND              2
#define ERR_UNKNOWN_MENU_SELECTION      252
#define ERR_FCLOSE_FAILED               253
#define ERR_UNKNOWN_FUNCTION            254
#define ERR_UNKNOWN                     255

#define MESS_INCORRECT_DATA             "Incorrect file\n"
#define MESS_FILE_NOT_FOUND             "File not found\n"
#define MESS_UNKNOWN_MENU_SELECTION     "Unknown menu case\n"
#define MESS_FCLOSE_FAILED              "Fclose failed\n"
#define MESS_UNKNOWN_FUNCTION           "Unknown function\n"
#define MESS_UNKNOWN                    "Unknown error\n"

#endif // __ERRORS_H__
