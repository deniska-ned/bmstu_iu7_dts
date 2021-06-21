#ifndef __MESSAGES_H__

#define __MESSAGES_H__

#define MESS_MENU \
"МЕНЮ:\n" \
"1. Добавить слово вручную\n" \
"2. Добавить слово из файла\n" \
"3. Удалить слово\n" \
"\n" \
"4. Вывод слов в обратном порядке\n" \
"\n" \
"5. Вывод текущего состояния стека\n" \
"6. Вывод массива свободных адресов\n" \
"\n" \
"7. Вывод статистики\n" \
"\n" \
"0. Выход\n" \

#define MESS_MENU_ASK \
"Ваш выбор: "

#define MESS_EXIT \
"Выход\n"

#define MESS_INCORRECT_INPUT \
"Введено некорректное значение\n"

#define MESS_CASE_EXIT \
"Выход\n"

#define MESS_NOT_REALISE_YET \
"Не реализовано еще\n"

#define MESS_WORD_ENTER \
"Введите слово: "

#define MESS_LIST \
"Список "

#define MESS_VECTOR \
"Массив "

#define MESS_STACK_IS_EMPTY \
"Стэк пуст\n"

#define MESS_DEL_WORD \
"Удаление слова из стека\n"

#define MESS_ADDRESSES \
"Адреса свободных областей:\n"

#define MESS_ARRAY_IS_EMPTY \
"Массив пуст\n"

#define MESS_WORD_COUNT_INPUT \
"Введите количество слов: "

#define MESS_UNABLE_OPEN_FILE \
"Невозможно открыть файл"

#define MESS_STAT \
"                    %20s %20s\n" \
"Размер              %20zu %20zu (выделено %zu)\n" \
"Время заполнения    %20zu %20zu\n" \
"Время осбовождения  %20zu %20zu\n"


#define MESS_STAT_2 \
"0_0            Время заполнения   Время осбовождения    Занимаемая память\n"\
"Массив     %20zu %20zu %20zu (Всего выделено: %zu)\n"\
"Список     %20zu %20zu %20zu\n"\

#define MESS_INCORRECT \
"Некорректный ввод\n"

#endif // __MESSAGES_H__
