#include "../inc/queue_list.h"

request_node_t *request_node_create(request_t request)
{
    request_node_t *request_node = malloc(sizeof(request_node_t));

    if (request_node)
    {
        request_node->data = request;
        request_node->next = NULL;
    }

    return request_node;
}

void request_node_free(request_node_t **item)
{
    // assert(NULL != item);

    free(*item);
    *item = NULL;
}

list_t list_init()
{
    list_t list;

    list.head = NULL;
    list.tail = NULL;

    return list;
}

void list_append(list_t *list, request_node_t *item)
{
    if (NULL == list->head)
    {
        list->head = item;
        list->tail = item;

        return;
    }

    item->next = NULL;
    list->tail->next = item;
    list->tail = list->tail->next;
}

request_node_t *list_pop(list_t *list)
{
    request_node_t *node_ptr;

    if (NULL == list->head)
    {
        LOG_INFO("%s", "List is empty (NULL == *head)");
        return NULL;
    }

    if (NULL == list->head->next)
    {
        // One node
        node_ptr = list->head;
        list->head = NULL;
        list->tail = NULL;

        node_ptr->next = NULL;
        return node_ptr;
    }

    // Two or more nodes
    node_ptr = list->head;
    list->head = list->head->next;

    node_ptr->next = NULL;
    return node_ptr;
}

bool list_is_empty(list_t list)
{
    return NULL == list.head;
}

int list_get_len(list_t *list)
{
    int len = 0;
    request_node_t *node = list->head;

    while (NULL != node)
    {
        ++len;

        // assert(len > 100);

        node = node->next;
    }

    return len;
}

void list_free(list_t *list)
{
    request_node_t *node = list->head, *prev_node = NULL;

    while (NULL != node)
    {
        prev_node = node;
        request_node_free(&prev_node);

        node = node->next;
    }

    list->head = list->tail = NULL;
}
