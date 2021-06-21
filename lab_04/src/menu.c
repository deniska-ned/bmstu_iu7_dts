#include "../inc/menu.h"

int menu_case_add_word_manually(stack_vector_t *stack_vector,
list_item_t **stack_list_head, vector_t *addresses)
{
    int rc;

    char buffer[MAX_WORD_LEN + 1];
    printf(MESS_WORD_ENTER);
    rc = read_word(stdin, buffer);
    goto_newline(stdin);

    if (EOF == rc)
    {
        LOG_ERROR("%s", "EOF stdin");
        return EOF_RECEIVED;
    }

    list_item_t *new_list_item = list_item_create(buffer);

    if (NULL == new_list_item)
    {
        LOG_ERROR("%s", "Allocation for new list item failed");
        return ALLOCATION_FAILED;
    }

    *stack_list_head = list_push(*stack_list_head, new_list_item);

    stack_vector_push(stack_vector, buffer);

    vector_del_ptr(addresses, *stack_list_head);

    return OKAY;
}

int read_word_count(int *word_count)
{
    int rc;

    printf(MESS_WORD_COUNT_INPUT);
    rc = scanf("%d", word_count);

    if (1 != rc)
    {
        LOG_ERROR("%s", "Unable to read word count to int");
        printf(MESS_INCORRECT_INPUT);
        goto_newline(stdin);
        return READ_WORD_COUNT_FAILED;
    }

    if (*word_count < 0)
    {
        LOG_ERROR("Word count is negative: %d", *word_count);
        return READ_WORD_COUNT_FAILED;
    }

    if (*word_count > MAX_WORD_COUNT)
    {
        LOG_ERROR("Word count exceeded: %d; Max: %zu", *word_count,
        MAX_WORD_COUNT);
        return READ_WORD_COUNT_FAILED;
    }

    return OKAY;
}

int menu_case_add_words_from_file(stack_vector_t *stack_vector,
list_item_t **stack_list_head, vector_t *addresses, char *filename, 
int word_count)
{
    FILE *f = fopen(filename, "r");
    char buffer[MAX_WORD_LEN + 1];

    if (NULL == f)
    {
        LOG_ERROR("Unable to open file %s", filename);
        printf(MESS_UNABLE_OPEN_FILE " %s", filename);
        return FILE_NOT_FOUND;
    }

    for (int i = 0; i < word_count; ++i)
    {
        read_word(f, buffer);
        list_item_t *new_list_item = list_item_create(buffer);

        if (NULL == new_list_item)
        {
            LOG_ERROR("%s", "Allocation for new list item failed");
            return ALLOCATION_FAILED;
        }

        *stack_list_head = list_push(*stack_list_head, new_list_item);

        stack_vector_push(stack_vector, buffer);

        vector_del_ptr(addresses, *stack_list_head);
    }

    return OKAY;
}

void menu_case_del_word(stack_vector_t *stack_vector,
list_item_t **stack_list_head, vector_t *addresses)
{
    printf(MESS_DEL_WORD);
    if (NULL == *stack_list_head)
    {
        LOG_ERROR("%s", "Stack is empty");
        printf(MESS_STACK_IS_EMPTY);
        return;
    }

    vector_add_ptr(addresses, *stack_list_head);

    char buffer[MAX_WORD_LEN + 1];
    printf(MESS_LIST ": %s\n", list_pop(stack_list_head, buffer));
    printf(MESS_VECTOR ": %s\n", stack_vector_pop(stack_vector, buffer));
    printf("\n");
}

void menu_case_output(stack_vector_t *stack_vector,
list_item_t **stack_list_head, vector_t *addresses)
{
    char buffer[MAX_WORD_LEN + 1];
    size_t start_ticks, end_ticks, list_print_ticks, vector_print_ticks;

    list_item_t *ptr = *stack_list_head;
    while (NULL != ptr)
    {
        vector_add_ptr(addresses, ptr);
        ptr = ptr->next;
    }

    // Size count

    size_t len = list_len(*stack_list_head);
    size_t vector_size = (unsigned) len * (MAX_WORD_LEN + 1);
    size_t list_size = (unsigned) len * sizeof(list_item_t);

    printf(MESS_LIST NEW_LINE);
    start_ticks = curr_ticks();
    while (NULL != list_pop(stack_list_head, buffer))
        printf("%s\n", buffer);
    end_ticks = curr_ticks();
    list_print_ticks = end_ticks - start_ticks;

    printf("\n");

    printf(MESS_VECTOR NEW_LINE);
    start_ticks = curr_ticks();
    while (NULL != stack_vector_pop(stack_vector, buffer))
        printf("%s\n", buffer);
    end_ticks = curr_ticks();
    vector_print_ticks = end_ticks - start_ticks;

    printf("\nВремя массива: %zu\nВремя списка: %zu\n",
    vector_print_ticks, list_print_ticks);
    printf("\nРазмер массива: %zu\nРазмер списка: %zu\n",
    vector_size, list_size);
}

void menu_case_output_debug(stack_vector_t *stack_vector,
list_item_t *stack_list_head)
{
    list_item_t *list_head = stack_list_head;

    printf("\n\tList:\n");
    while (NULL != list_head)
    {
        printf("\t%s\n", list_head->word);
        list_head = list_head->next;
    }

    printf("\n\tArray:\n");
    char *cur_ptr = stack_vector_get_cur_ptr(stack_vector);
    char *left_border = stack_vector_get_left_border(stack_vector);

    while (cur_ptr >= left_border)
    {
        printf("\t%s\n", cur_ptr);
        cur_ptr -= MAX_WORD_LEN + 1;
    }
}

void menu_case_output_addresses(vector_t *addresses)
{
    printf(MESS_ADDRESSES);

    size_t len = vector_get_used_length(addresses);

    printf("Длина: %zu\n", len);

    if (0 == len)
        printf(MESS_ARRAY_IS_EMPTY);

    for (size_t i = 0; i < len; ++i)
        printf("%p\n", vector_get_ptr_to_ptr_to(addresses, i));
}

int menu_case_stat(stack_vector_t *stack_vector,
list_item_t **stack_list_head, vector_t *addresses, char *filename, 
int word_count)
{
    size_t start_ticks, end_ticks;

    size_t vector_filling_ticks, list_filling_ticks;
    size_t vector_print_ticks, list_print_ticks;
    size_t vector_size, list_size;
    size_t vector_availible_size = (MAX_WORD_COUNT * (MAX_WORD_LEN + 1));

    char buffer[MAX_WORD_LEN + 1];

    // Erase stack

    list_item_t *ptr = *stack_list_head;
    while (NULL != ptr)
    {
        vector_add_ptr(addresses, ptr);
        ptr = ptr->next;
    }

    // printf(MESS_VECTOR NEW_LINE);
    while (NULL != stack_vector_pop(stack_vector, buffer))
        ;

    printf("\n");
    // printf(MESS_LIST NEW_LINE);
    while (NULL != list_pop(stack_list_head, buffer))
        ;

    // New filling stack

    FILE *f = fopen(filename, "r");

    if (NULL == f)
    {
        LOG_ERROR("Unable to open file %s", filename);
        printf(MESS_UNABLE_OPEN_FILE " %s", filename);
        return FILE_NOT_FOUND;
    }

    start_ticks = curr_ticks();
    for (int i = 0; i < word_count; ++i)
    {
        read_word(f, buffer);
        list_item_t *new_list_item = list_item_create(buffer);

        if (NULL == new_list_item)
        {
            LOG_ERROR("%s", "Allocation for new list item failed");
            return ALLOCATION_FAILED;
        }

        *stack_list_head = list_push(*stack_list_head, new_list_item);
    }
    end_ticks = curr_ticks();
    list_filling_ticks = end_ticks - start_ticks;

    rewind(f);

    start_ticks = curr_ticks();
    for (int i = 0; i < word_count; ++i)
    {
        read_word(f, buffer);
        stack_vector_push(stack_vector, buffer);
    }
    end_ticks = curr_ticks();
    vector_filling_ticks = end_ticks - start_ticks;

    // Size count

    vector_size = (unsigned) word_count * (MAX_WORD_LEN + 1);
    list_size = (unsigned) word_count * sizeof(list_item_t);

    // Output stack

    // printf(MESS_LIST NEW_LINE);
    start_ticks = curr_ticks();
    while (NULL != list_pop(stack_list_head, buffer))
        ; // printf("%s\n", buffer);
    end_ticks = curr_ticks();
    list_print_ticks = end_ticks - start_ticks;

    printf("\n");

    // printf(MESS_VECTOR NEW_LINE);
    start_ticks = curr_ticks();
    while (NULL != stack_vector_pop(stack_vector, buffer))
        ; // printf("%s\n", buffer);
    end_ticks = curr_ticks();
    vector_print_ticks = end_ticks - start_ticks;

    // Output stat

    // printf(MESS_STAT, "Список", "Массив",
    // list_size, vector_size, vector_availible_size,
    // list_filling_ticks, vector_filling_ticks,
    // list_print_ticks, vector_print_ticks);

    printf(MESS_STAT_2, vector_filling_ticks, vector_print_ticks, vector_size,
    vector_availible_size, list_filling_ticks, list_print_ticks, list_size);

    return OKAY;
}

int menu_start(stack_vector_t **stack_vector, list_item_t **stack_list_head,
vector_t **addresses)
{
    int menu_choice;
    int rc, grc = OKAY;

    do
    {
        printf(NEW_LINE MESS_MENU NEW_LINE MESS_MENU_ASK);
        
        rc = scanf("%d", &menu_choice);

        goto_newline(stdin);
        printf(NEW_LINE);

        if (1 != rc)
        {
            LOG_WARNING("%s", "Unable to scanf choice to int");
            
            printf(MESS_INCORRECT_INPUT);
            continue;
        }

        switch (menu_choice)
        {
            case MENU_CASE_EXIT:
                printf(MESS_EXIT);
                break;
            case MENU_CASE_ADD_WORD_MANUALLY:
                if (list_len(*stack_list_head) > MAX_WORD_COUNT)
                {
                    printf("Стэк заполнен\n");
                    break;
                }
                menu_case_add_word_manually(*stack_vector, stack_list_head,
                *addresses);
                break;
            case MENU_CASE_ADD_WORDS_FROM_FILE:
                {
                    int word_count;
                    if (OKAY != read_word_count(&word_count))
                    {
                        printf(MESS_INCORRECT);
                        break;
                    }
                    if ((unsigned) word_count + list_len(*stack_list_head) > MAX_WORD_COUNT)
                    {
                        printf(MESS_INCORRECT);
                        break;
                    }
                    menu_case_add_words_from_file(*stack_vector,
                    stack_list_head, *addresses, FILENAME, word_count);
                    break;
                }
            case MENU_CASE_DEL_WORD:
                menu_case_del_word(*stack_vector, stack_list_head, *addresses);
                break;
            case MENU_CASE_OUTPUT:
                menu_case_output(*stack_vector, stack_list_head, *addresses);
                break;
            case MENU_CASE_OUTPUT_DEBUG:
                menu_case_output_debug(*stack_vector,
                *stack_list_head);
                break;
            case MENU_CASE_OUTPUT_ADDRESSES:
                menu_case_output_addresses(*addresses);
                break;
            case MENU_CASE_STAT:
                {
                    int word_count;
                    if (OKAY != read_word_count(&word_count))
                    {
                        printf(MESS_INCORRECT);
                        break;
                    }
                    menu_case_stat(*stack_vector,
                    stack_list_head, *addresses, FILENAME, word_count);
                    break;
                }
            default:
                LOG_WARNING("Incorrect number menu choice: %d", menu_choice);
                printf(MESS_INCORRECT_INPUT);
        }

    }
    while (MENU_CASE_EXIT != menu_choice);

    return grc;
}
