#include "../inc/stat.h"

#define MAX(X, Y) X >= Y ? X : Y

#define TOL(X, Y) (fabs((double) X - (double) Y) / (double) Y) * 100.0

#define ARR_LEN                         5

void on_stat_menu_case()
{
    int len_arr[ARR_LEN] = {1000, 2000, 5000, 10000, 20000};

    printf("\nВремя измеряется в тактах\n");

    printf("\n#### Список\n\n");

    printf("|Количество элементов|Добавление|Удаление|Размер|\n");
    printf("|--------------------|----------|--------|------|\n");

    for (int i = 0; i < ARR_LEN; ++i)
    {
        size_t append_time, remove_time, size;

        list_t list = list_init();

        size_t end;
        size_t start = curr_ticks();
        for (int j = 0; j < len_arr[i]; ++j)
        {
            request_t request = {.value = j};
            request_node_t *node = request_node_create(request);
            list_append(&list, node);
        }
        end = curr_ticks();

        append_time = end - start;

        size = (size_t) len_arr[i] * sizeof(request_node_t);

        start = curr_ticks();

        for (int j = 0; j < len_arr[i]; ++j)
        {
            request_node_t *node = list_pop(&list);
            request_node_free(&node);
        }
        end = curr_ticks();

        remove_time = end - start;

        // printf("|%20d|%10zu|%8zu|%6zu|\n", len_arr[i], append_time, remove_time, size);
        printf("|%20d|%9zuk|%7zuk|%6zu|\n", len_arr[i], append_time / 1000, remove_time / 1000, size);
    }

    printf("\n#### Вектор\n\n");

    printf("|Количество элементов|Добавление|Удаление|Размер|\n");
    printf("|--------------------|----------|--------|------|\n");

    for (int i = 0; i < ARR_LEN; ++i)
    {
        size_t append_time, remove_time, size;

        queue_vector_t *vector = queue_vector_allocate((size_t) len_arr[i]);

        size_t end;

        size_t start = curr_ticks();
        for (int j = 0; j < len_arr[i]; ++j)
        {
            request_t request = {.value = j};
            queue_vector_append(vector, &request);
        }
        end = curr_ticks();
        append_time = end - start;

        size = queue_vector_get_size(vector);

        start = curr_ticks();
        for (int j = 0; j < len_arr[i]; ++j)
        {
            request_t request;
            queue_vector_pop(vector, &request);
        }
        end = curr_ticks();
        remove_time = end - start;

        // printf("|%20d|%10zu|%8zu|%6zu|\n", len_arr[i], append_time, remove_time, size);
        printf("|%20d|%9zuk|%7zuk|%6zu|\n", len_arr[i], append_time / 1000, remove_time / 1000, size);

        queue_vector_free(vector);
    }
}

void print_expected_results(service_unit_t service)
{
    double avg_one_cycle_processing_time = (service.max_service_time -
    service.min_service_time) / 2.0;

    double avg_one_whole_processing_time = (avg_one_cycle_processing_time *
    service.one_request_cycle_count);

    double avg_whole_processing_time = (avg_one_whole_processing_time *
    service.ended_request_count);

    double avg_request_arriving_time = (service.max_arrival_time -
    service.min_arrival_time) / 2.0;

    double avg_whole_arriving_time = (avg_request_arriving_time *
    service.ended_request_count);

    double downtime = (avg_whole_arriving_time > avg_whole_processing_time ?
    avg_whole_arriving_time - avg_whole_processing_time : 0.0);

    printf("\n\nОжидаемые результаты:\n");
    printf("Среднее время обработки одной заявки в одном цикле: %.2lf\n",
    avg_one_cycle_processing_time);

    printf("Полное время обработки одной заявки: %.2lf\n",
    avg_one_whole_processing_time);

    printf("Время обработки необходимого числа заявок: %.2lf\n\n",
    avg_whole_processing_time);

    printf("Средний интервал прибытия новой заявки: %.2lf\n",
    avg_request_arriving_time);

    printf("Время прибытия необходимого числа заявок: %.2lf\n",
    avg_whole_arriving_time);

    printf("Время простоя: %.2lf\n", downtime);
}

void modeling_stat_print(modeling_list_t *lmodel, modeling_vector_t *vmodel,
service_unit_t *service)
{
    assert(service);
    double avg_one_cycle_processing_time = (service->max_service_time -
    service->min_service_time) / 2.0;

    double avg_one_whole_processing_time = (avg_one_cycle_processing_time *
    service->one_request_cycle_count);

    double avg_whole_processing_time = (avg_one_whole_processing_time *
    service->ended_request_count);

    double avg_request_arriving_time = (service->max_arrival_time -
    service->min_arrival_time) / 2.0;

    double avg_whole_arriving_time = (avg_request_arriving_time *
    service->ended_request_count);

    double downtime = (avg_whole_arriving_time > avg_whole_processing_time ?
    avg_whole_arriving_time - avg_whole_processing_time : 0.0);

    double time = MAX(avg_whole_arriving_time, avg_whole_processing_time);

    printf("\n\nОжидаемые результаты:\n");
    printf("Среднее время обработки одной заявки в одном цикле: %.2lf\n",
    avg_one_cycle_processing_time);

    printf("Полное время обработки одной заявки: %.2lf\n",
    avg_one_whole_processing_time);

    printf("Время обработки необходимого числа заявок: %.2lf\n\n",
    avg_whole_processing_time);

    printf("Средний интервал прибытия новой заявки: %.2lf\n",
    avg_request_arriving_time);

    printf("Время прибытия необходимого числа заявок: %.2lf\n",
    avg_whole_arriving_time);

    printf("Время простоя: %.2lf\n", downtime);

    printf("\nПолученные результаты\n");

    printf("|                          | Список | Вектор |\n");
    printf("|--------------------------|--------|--------|\n");
    printf("|Кол-во вошедших заявок    |%8d|%8d|\n",
    lmodel->created_request_count, vmodel->created_request_count);
    printf("|Кол-во обработанных заявок|%8d|%8d|\n",
    lmodel->processed_request_count, vmodel->processed_request_count);
    printf("|Кол-во покинувших заявок  |%8d|%8d|\n",
    lmodel->ended_request_count, vmodel->ended_request_count);
    printf("|Время простоя             |%8.2lf|%8.2lf|\n",
    lmodel->downtime, vmodel->downtime);
    printf("|Среднее время в очереди   |%8.2lf|%8.2lf|\n",
    lmodel->avg_queue_time, vmodel->avg_queue_time);
    printf("|Длина списка заявок       |%8d|%8d|\n",
    list_get_len(&lmodel->request_list), queue_vector_get_len(vmodel->request_vector));
    printf("|Средняя длина списка      |%8.2lf|%8.2lf|\n",
    lmodel->avg_list_len, vmodel->avg_list_len);
    printf("|Общее время моделирования |%8.2lf|%8.2lf|\n",
    lmodel->end_modeling_time, vmodel->end_modeling_time);
    printf("|Погрешность               |%8.2lf|%8.2lf|\n",
    TOL(lmodel->end_modeling_time, time), TOL(vmodel->end_modeling_time, time));
}
