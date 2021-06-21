#ifndef __MENU_H__

#define __MENU_H__

#include <stdio.h>

#include "services.h"
#include "stat.h"

#define MENU_MESS \
"Меню:\n" \
"0 - выход\n" \
"1 - запуск со значениями по умолчанию\n" \
"2 - запуск со своими значениями\n" \
"3 - замеры времени и памяти\n" \
"\n" \
"Ваш выбор: "

int run_menu();

#endif // __MENU_H__
