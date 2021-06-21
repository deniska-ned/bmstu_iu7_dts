#ifndef __QUEUE_LIST_H__

#define __QUEUE_LIST_H__

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "macrologger.h"

#include "request.h"

typedef struct request_node request_node_t;

struct request_node
{
    request_t data;
    request_node_t *next;
};

typedef struct list list_t;

struct list
{
    request_node_t *head;
    request_node_t *tail;
};

request_node_t *request_node_create(request_t request);

void request_node_free(request_node_t **item);

list_t list_init();

void list_append(list_t *list, request_node_t *item);

request_node_t *list_pop(list_t *list);

bool list_is_empty(list_t list);

int list_get_len(list_t *list);

void list_free(list_t *list);

#endif // __QUEUE_LIST_H__
