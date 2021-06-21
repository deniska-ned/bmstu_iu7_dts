#include "../inc/list.h"

list_item_t *list_item_create(char *word)
{
    list_item_t *item = malloc(sizeof(list_item_t));
    LOG_DEBUG("Address of new list item: %p", (void *) item);

    if (item)
    {
        strncpy(item->word, word, MAX_WORD_LEN);
        item->next = NULL;
    }

    return item;
}

void list_item_free(list_item_t *list_item)
{
    free(list_item);
}

list_item_t *list_push(list_item_t *head, list_item_t *item)
{
    item->next = head;

    return item;
}

char *list_pop(list_item_t **head, char *str)
{
    if (NULL == *head)
    {
        LOG_WARNING("%s", "All item removed");
        return NULL;
    }

    strncpy(str, (*head)->word, MAX_WORD_LEN);

    list_item_t *new_head = (*head)->next;

    list_item_free(*head);

    *head = new_head;

    return str;
}

size_t list_len(list_item_t *head)
{
    size_t len = 0;

    while (NULL != head)
    {
        ++len;
        head = head->next;
    }

    return len;
}
