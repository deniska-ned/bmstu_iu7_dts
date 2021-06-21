# Отчет по Лабораторной работе №4 "Работа со стеком"

Вариант: 3

Студент: **Недолужко Денис**

Группа: **ИУ7-33Б**

Год: 2020
## Описание условия задачи

Цель работы: реализовать операции работы со стеком, который представлен в
виде массива (статического или динамического) и в виде односвязного списка,
оценить преимущества и недостатки каждой реализации, получить представление о
механизмах выделения и освобождения памяти при работе с динамическими
структурами данных.

## Описание ТЗ

### Описание задачи

Создать программу работы со стеком,
выполняющую операции добавление,
удаления элементов и вывод текущего
состояния стека. Реализовать стек:
а) массивом; б) списком. Все стандартные
операции со стеком должны быть оформлены
подпрограммами. При реализации стека
списком в вывод текущего состояния стека
добавить просмотр адресов элементов стека и
создать свой список или массив свободных
областей (адресов освобождаемых элементов)
с выводом его на экран. Элементами стека являются слова. Распечатайте
слова в обратном порядке.

### Входные данные

1. Слова вводятся вручную
2. Слова читаются из файла

### Выходные данные

Печатается содерживае стека как для списка, так и для массива. Так же
выводятся количество тактов за заполнение стека, количество тактов на
освобождение стека, занимаемая память.

### Способ обращения к программе

Запускается в терминале командой `./app.exe` в папке с программой.

### Описание возможных аварийных ситуаций

Некорректный ввод пользователя. Сообщение `Некорректный ввод`.

## Таблица с результатами измерений

### 100 элементов

|               |Время заполнения (тики)  |Время осбовождения (тики)   |Занимаемая память|
|-|-|-|-|
|Массив         |           80992   |             22610    |             1500 (Всего выделено: 3000000)|
|Список         |        10150602   |             31504    |             2400|


### 1000 элементов

|               |Время заполнения  (тики) |Время осбовождения   (тики) |Занимаемая память|
|-|-|-|-|
|Массив         |          745901   |            225860    |            15000 (Всего выделено: 3000000)|
|Список         |          922960   |            345486    |            24000|
 
### 10000 элементов

|               |Время заполнения  (тики) |Время осбовождения (тики)   |Занимаемая память|
|-|-|-|-|
|Массив         |         2815474   |            646088    |           150000 (Всего выделено: 3000000)|
|Список         |         7834069   |            957768    |           240000|

### 100000 элементов

|               |Время заполнения (тики)  |Время осбовождения  (тики)  |Занимаемая память|
|-|-|-|-|
|Массив         |        20520949   |           5571558    |          1500000 (Всего выделено: 3000000)|
|Список         |        30511565   |           9027771    |          2400000|

## Вывод

Стек реализованный массивом всегда выигрывает по времени, как по заполнению
так и по очистке. Это связано с тем, чем при работе со списком требуется
каждый раз выделять память под элементы, в то время, как память под массив
выделяется один раз в начале. Однако массив проигрывает по памяти, если
неиспользуемая память
больше памяти, выделяемой под указатели списка. В данном случае массив
проигрывает по памяти, если заполнен меньше чем на 62.5%.
Следовательно массив выгоднее использовать, когда известна длина длина стека,
в противном случае - список.

## Вопросы

1. Что такое стек?\
Стек – это последовательный список с переменной длиной, в котором включение и
исключение элементов происходит только с одной стороны – с его вершины. Стек
функционирует по принципу: последним пришел – первым ушел, Last In – First
Out (LIFO).
2. Каким образом и сколько памяти выделяется под хранение стека при различной
его реализации?\
При хранении стека в виде списка память под него выделяет в куче. Для храния
одного элемента списка требуется память под данные и под указатель на
следущий элемент списка. В памяти может храниться не в виде непрерывного
блока.\
При хранении стека в виде массива память под него выделятся либо в стека
(в случае статического массива), либо в куче (в случае динамического массива).
Хранение одного элемента требует только память для данных. В памяти
хранится непрерывным блоком.
3. Каким образом освобождается память при удалении элемента стека при
различной реализации стека?\
Освобождение памяти при удалении элемента стека в случае списка подразумевает
под собой смещение указателя на голову и освобождение памяти элемента списка.
В случае массива память не освобождается, только смещается указатель.
4. Что происходит с элементами стека при его просмотре?\
Элементы покидают стек
5. Каким образом эффективнее реализовывать стек? От чего это зависит?\
Стек реализованный массивом всегда выигрывает по времяти, однако может
может проигрывать по памяти. Если заранее известна длина стека, то всегда
выгоднее использовать массив. Если же длина стека заранее неизвестна, то
приходится выбирать между скоростью выполнения и занимаемой памятью.