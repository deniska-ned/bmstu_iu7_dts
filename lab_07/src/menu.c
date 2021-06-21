#include "../inc/menu.h"

int menu_start()
{
    int rc;
    int choice = MENU_EXIT + 1;

    unsigned src, dst;
    int weight;

    struct graph *graph = graph_init();

    if (NULL == graph)
    {
        printf(MESS_ALLOCATION_FAILED);
        return ALLOCATION_FAILED;
    }

    while (MENU_EXIT != choice)
    {
        printf(MESS_MENU MESS_MENU_CHOICE);
        
        rc = scanf("%d", &choice);
        goto_newline(stdin);
        if (1 != rc)
        {
            printf(MESS_INCORRECT_INPUT);
            continue;
        }

        printf("\n");
        switch (choice)
        {
            case MENU_EXIT:
                printf(MESS_EXIT);
                break;
            case MENU_ADD_FROM_FILE:
                {
                    char *filename = NULL;
                    size_t buffer_len = 0;
                    printf(MESS_INPUT_FILENAME);
                    ssize_t readed = getline(&filename, &buffer_len, stdin);

                    if (EOF == readed)
                    {
                        printf(MESS_INCORRECT_INPUT);
                        break;
                    }

                    if ('\n' == filename[readed - 1])
                        filename[readed-- - 1] = '\0';

                    if (OKAY != graph_add_node_from_file(graph, filename))
                        printf(MESS_FILE_READING_ERROR);
                    else
                        printf(MESS_FILE_READING_SUCCESS);

                    free(filename);
                }
                break;
            case MENU_ADD_MANUALLY:
                printf("Введите откуда, куда, вес: ");
                if (3 != scanf("%u %u %d", &src, &dst, &weight))
                {
                    printf(MESS_INCORRECT_INPUT);
                    break;
                }
                if (OKAY != graph_add_node(graph, src, dst, weight))
                {
                    printf(MESS_ALLOCATION_FAILED);
                }
                else
                {
                    printf(MESS_ADDING_SUCCESS);
                }
                break;
            case MENU_GRAPH_OUTPUT:
                graph_draw(graph);
                break;
            case MENU_SEARCH:
                {
                    vector_t *vector;
                    unsigned start_name;
                    printf("Введите стартовый узел: ");
                    if (1 != scanf("%u", &start_name))
                    {
                        printf(MESS_INCORRECT_INPUT);
                        break;
                    }
                    rc = graph_bellman_ford_mod(graph, &vector, start_name);
                    if (rc != OKAY)
                    {
                        printf(MESS_ALLOCATION_FAILED);
                        break;
                    }
                    int max_weight;
                    printf("Введите максимальную длину пути: ");
                    if (1 == scanf("%d", &max_weight))
                    {
                        graph_draw_and_select(graph, vector, max_weight, start_name);
                        graph_way_len_debug_print(stderr, vector);
                    }
                }
                break;
            default:
                printf(MESS_INCORRECT_INPUT);
        }
        printf("\n");
    }

    graph_free(graph);

    return OKAY;
}
