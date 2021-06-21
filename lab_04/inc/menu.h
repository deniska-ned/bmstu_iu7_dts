#ifndef __MENU_H__

#define __MENU_H__

#include <stdio.h>

#include "messages.h"
#include "macrologger.h"
#include "nonstdio.h"
#include "vector.h"
#include "stack_vector.h"
#include "list.h"
#include "timer.h"

#define FILENAME "./world_and_peace.txt"

#define MENU_CASE_EXIT                  0
#define MENU_CASE_ADD_WORD_MANUALLY     1
#define MENU_CASE_ADD_WORDS_FROM_FILE   2
#define MENU_CASE_DEL_WORD              3
#define MENU_CASE_OUTPUT                4
#define MENU_CASE_OUTPUT_DEBUG          5
#define MENU_CASE_OUTPUT_ADDRESSES      6
#define MENU_CASE_STAT                  7

#define READ_WORD_COUNT_FAILED          1
#define FILE_NOT_FOUND                  2

#define OKAY                            0
#define EOF_RECEIVED                    1
#define ALLOCATION_FAILED               128
int menu_case_add_word_manually(stack_vector_t *stack_vector,
list_item_t **stack_list_head, vector_t *adress_vector);

#define OKAY                            0
int menu_start(stack_vector_t **stack_vector, list_item_t **stack_list_head,
vector_t **addresses);

#endif // __MENU_H__
