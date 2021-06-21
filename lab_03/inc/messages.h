#ifndef __MESSAGES_H__

#define __MESSAGES_H__

#define MESS_MENU \
"Меню:\n" \
"1. Заполнение матрицы автоматически\n" \
"2. Заполнение матрицы вручную\n" \
"3. Расчет и вывод статистики\n" \
"\n" \
"0. Выход без исполнения\n"

#define MESS_MENU_CHOICE \
"Ваш выбор: "

#define MESS_INCORRECT_INPUT "Некорректный ввод\n"

#define MESS_EXIT "Выход\n"

#define MESS_ROW_COL_COUNT_INPUT \
"Введите количество строк и столбцов матрицы: "

#define MESS_COVER_COUNT_INPUT \
"Введите покрытие ненулевыми элементами в %% для матрицы и столбца: "

#define TABLE_HEADER_STATICTICS \
"──────┼──┼────┼────┼──────┼──────┼──────────┼──────────┼──────────┼───────────\n" \
"      │  │    │    │matrix│column│          │matrix    │column    │product    \n" \
"      │ i│rows│cols│mcover│ccover│     ticks│size   [B]│size   [B]│size    [B]\n" \
"──────┼──┼────┼────┼──────┼──────┼──────────┼──────────┼──────────┼───────────\n"

#define MESS_ROW_COL_NUMCOUNT_INPUT \
"Введите число строк и столбцов и колво ненулевых значений: "

#define MESS_ROW_COL_VALUE_INPUT "Ввидети индекс строки, столбца и значение: "

#define MESS_ROW_VALUE_INPUT "Ввидети индекс строки и значение: "

#define MESS_NUM_COUNT "Введите число чисел в разреженном стобце: "

#endif // __MESSAGES_H__
