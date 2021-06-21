#ifndef __LIST_H__

#define __LIST_H__

#include <string.h>
#include <stdlib.h>

#include "word_info.h"
#include "macrologger.h"

struct list_item
{
    char word[MAX_WORD_LEN + 1];
    struct list_item *next;
};

typedef struct list_item list_item_t;

/**
 * Create list_item_t and fill it data: copy word to item.word and
 * item.next=NULL.
 *
 * @return NULL if allocation failed; not NULL - ptr to this element
 */
list_item_t *list_item_create(char *word);

/**
 * Free list_item
 */
void list_item_free(list_item_t *list_item);

/**
 * Item.next assign value to head list
 *
 * @return Ptr - new head
 */
list_item_t *list_push(list_item_t *head, list_item_t *item);

/**
 * Free the first list item
 *
 * @return New head (second element may be NULL).
 */
char *list_pop(list_item_t **head, char *str);

size_t list_len(list_item_t *head);

#endif // __LIST_H__
