#include "../inc/service_list.h"

double lm_get_new_arraval_time(service_unit_t *service)
{
    return random_double_in_range(service->min_arrival_time,
    service->max_arrival_time);
}

double lm_get_new_service_end_time(service_unit_t *service)
{
    return random_double_in_range(service->min_service_time,
    service->max_service_time);
}

double lm_get_curr_time(modeling_list_t *model)
{
    double arravel_time = model->next_arrival_time;
    double service_end_time = model->next_service_end_time;

    LOG_DEBUG("arrival_time = %.2lf; service_end_time = %.2lf", arravel_time,
    service_end_time);
    LOG_DEBUG("isnan(arrival_time) = %s; isnan(service_end_time) = %s",
    BOOL_TO_STR(isnan(arravel_time)), BOOL_TO_STR(isnan(service_end_time)));

    assert(!(isnan(arravel_time) && isnan(service_end_time)));

    assert(!isnan(arravel_time));

    if (isnan(service_end_time))
    {
        LOG_TRACE("Arrival time is current: %.3lf (another is nan)",
        arravel_time);
        return arravel_time;
    }

    double res;

    if (arravel_time <= service_end_time)
    {
        LOG_TRACE("Arrival time is current: %.3lf ", arravel_time);
        res = arravel_time;
    }
    else
    {
        LOG_TRACE("Service end time is current: %.3lf", service_end_time);
        res = service_end_time;
    }

    return res;
}

void lm_print_modeling_data_each_100(modeling_list_t *model,
ptr_vector_t *ptr_vector)
{
    int list_len = list_get_len(&model->request_list);
    double avg_list_len = model->avg_list_len;
    int avg_list_len_count = model->avg_list_len_count;

    avg_list_len = update_avg(avg_list_len, avg_list_len_count, list_len);

    model->avg_list_len = avg_list_len;
    model->avg_list_len_count = ++avg_list_len_count;

    printf("Заявок покинуло ОА: %d\n", model->ended_request_count);
    printf("Заявок обработано: %d\n", model->processed_request_count);
    printf("Число заявок в очереди: %d\n", list_len);
    printf("Среднее число заявок в очереди: %.2lf\n", model->avg_list_len);
    printf("Среднее время проведённое в очереди: %.2lf\n", model->avg_queue_time);
    ptr_vector_print(stdout, ptr_vector);
    printf(MESS_LINE_SEPARATOR);
}

void lm_print_whole_modeling_data(modeling_list_t *model)
{
    printf("\nРезультат моделирования списка:\n");
    printf("Количество вошедших в систему заявок: %d\n", model->created_request_count);
    printf("Количество обработанных заявок: %d\n", model->processed_request_count);
    printf("Количество покинувших систему заявок: %d\n", model->ended_request_count);
    printf("Время простоя: %.2lf\n", model->downtime);
    printf("\n");
    printf("Среднее время в очереди: %.2lf\n", model->avg_queue_time);
    printf("Длина списка заявок: %d\n", list_get_len(&model->request_list));
    printf("Средняя длина списка: %.2lf\n", model->avg_list_len);
    printf("\n");
    printf("Общее время моделирования: %.2lf е.в.\n", model->end_modeling_time);
}

bool lm_move_request_to_service(modeling_list_t *model, service_unit_t *service,
ptr_vector_t *ptr_vector)
{
    request_node_t *request = list_pop(&model->request_list);
    ptr_vector_del(ptr_vector, request);

    if (NULL == request)
    {
        LOG_WARNING("%s", "List is empty");
        return false;
    }

    if (!isnan(model->downtime_start))
    {
        model->downtime += lm_get_curr_time(model) - model->downtime_start;
        model->downtime_start = NAN;
    }

    model->processing_request = request;

    if (0 == model->processing_request->data.processing_count)
    {
        model->processing_request->data.first_service_time = lm_get_curr_time(model);

        model->avg_queue_time = update_avg(model->avg_queue_time,
            model->avg_queue_time_count,
            model->processing_request->data.first_service_time -
            model->processing_request->data.creating_time);

        ++model->avg_queue_time_count;
    }

    model->next_service_end_time = (lm_get_curr_time(model) +
    lm_get_new_service_end_time(service));

    return true;
}

bool lm_is_time_to_exit(modeling_list_t *model,
service_unit_t *service)
{
    bool res = service->ended_request_count == model->ended_request_count;

    LOG_TRACE("%d/%d\n", model->ended_request_count,
    service->ended_request_count);

    LOG_TRACE("<< %s", BOOL_TO_STR(res));

    return res;
}

void lm_on_exit(/* modeling_list_t *model */)
{
    printf("The list modeling end\n");

    LOG_INFO("%s", "The modeling end\n");
}

bool lm_is_time_to_add_new_request(modeling_list_t *model)
{
    bool suitable_time = ((isnan(model->next_service_end_time) &&
    list_is_empty(model->request_list)) ||
    (model->next_arrival_time <= model->next_service_end_time));

    LOG_TRACE("<< suitable_time = %s", BOOL_TO_STR(suitable_time));

    return suitable_time;
}

void lm_on_add_new_request(modeling_list_t *model,
service_unit_t *service, ptr_vector_t *ptr_vector)
{
    request_t new = {
        .value = model->created_request_count,
        .processing_count = 0,
        .creating_time = lm_get_curr_time(model),
        .first_service_time = NAN
    };
    request_node_t *new_node = request_node_create(new);

    assert(NULL != new_node);

    
    ptr_vector_append(ptr_vector, new_node);
    list_append(&model->request_list, new_node);
    ++model->created_request_count;
    LOG_TRACE("%s", "New query append");

    model->next_arrival_time += lm_get_new_arraval_time(service);
}

bool lm_is_time_to_move_query_to_service(modeling_list_t *model)
{
    bool is_service_empty = NULL == model->processing_request;
    bool is_queue_not_empty = !list_is_empty(model->request_list);

    LOG_TRACE("is_service_empty = %s; is_queue_not_empty = %s",
    BOOL_TO_STR(is_service_empty), BOOL_TO_STR(is_queue_not_empty));

    bool res = is_service_empty && is_queue_not_empty;

    LOG_TRACE("<< %s", BOOL_TO_STR(res));

    return res;
}

void lm_on_move_queue_to_service(modeling_list_t *model, service_unit_t *service, ptr_vector_t *ptr_vector)
{
    bool res = lm_move_request_to_service(model, service, ptr_vector);

    assert(res);
}

bool lm_is_time_to_end_processing_request(modeling_list_t *model)
{
    bool is_service_not_empty = NULL != model->processing_request;
    bool is_suitable_time = (model->next_service_end_time <
    model->next_arrival_time);

    LOG_TRACE("is_service_not_empty = %s; is_suitable_time = %s",
    BOOL_TO_STR(is_service_not_empty), BOOL_TO_STR(is_suitable_time));

    bool res = is_service_not_empty && is_suitable_time;

    LOG_TRACE("<< %s", BOOL_TO_STR(res));

    return res;
}

void lm_on_end_processing_request(modeling_list_t *model,
service_unit_t *service, ptr_vector_t *ptr_vector)
{
    ++model->processed_request_count;
    int count = ++model->processing_request->data.processing_count;

    if (count >= service->one_request_cycle_count)
    {
        LOG_TRACE("Request was in service %d times. Free them",
        service->one_request_cycle_count);

        LOG_DEBUG("before free model->processing_request = %p",
        (void *) model->processing_request);

        request_node_free(&model->processing_request);
        ++model->ended_request_count;

        LOG_DEBUG("after  free model->processing_request = %p",
        (void *) model->processing_request);
    }
    else
    {
        ptr_vector_append(ptr_vector, model->processing_request);
        list_append(&model->request_list, model->processing_request);
    }

    model->processing_request = NULL;

    LOG_DEBUG("Now list len is %d", list_get_len(&model->request_list));

    if (list_is_empty(model->request_list))
    {
        // model->end_modeling_time = model->next_service_end_time;
        model->downtime_start = model->next_service_end_time;
        model->next_service_end_time = NAN;
    }
    else
    {
        bool res = lm_move_request_to_service(model, service, ptr_vector);
        assert(res);
    }
}

int list_service_modeling(modeling_list_t *model, service_unit_t service)
{
    ptr_vector_t *ptr_vector = ptr_vector_allocate(DEFAULT_PTR_VECTOR_LEN);
    if (NULL == ptr_vector)
    {
        LOG_ERROR("%s", "Allocation failed");
        printf("Ошибка выделения памяти");
        return 1;
    }
    int prev_ended_request_count_for_print = 0;

    while (true)
    {
        LOG_DEBUG("@@ %d; Next arrival time: %.5lf, next service end time: %.5lf; len: %d",
        model->processed_request_count, model->next_arrival_time,
        model->next_service_end_time, list_get_len(&model->request_list));

        #if LOG_LEVEL >= DEBUG_LEVEL
        request_node_t *head = model->request_list.head;
        if (NULL == head)
            fprintf(stderr, "->NULL");
        else
            fprintf(stderr, "->%d (%d)", head->data.value, head->data.processing_count);
        while (head != NULL)
        {
            head = head->next;
            if (NULL == head)
                fprintf(stderr, "->NULL");
            else
                fprintf(stderr, "->%d (%d)", head->data.value, head->data.processing_count);
        }
        fprintf(stderr, "\n");
        #endif

        if (0 == model->ended_request_count % OUTPUT_NUMBER &&
        prev_ended_request_count_for_print  != model->ended_request_count)
        {
            lm_print_modeling_data_each_100(model, ptr_vector);
            prev_ended_request_count_for_print = model->ended_request_count;
        }

        if (lm_is_time_to_exit(model, &service))
        {
            lm_on_exit(/* model */);
            model->end_modeling_time = lm_get_curr_time(model);
            model->ptr_vector_used_len = ptr_vector->used_length;
            break;
        }
        else if (lm_is_time_to_add_new_request(model))
        {
            lm_on_add_new_request(model, &service, ptr_vector);
        }
        else if (lm_is_time_to_move_query_to_service(model))
        {
            lm_on_move_queue_to_service(model, &service, ptr_vector);
        }
        else if (lm_is_time_to_end_processing_request(model))
        {
            LOG_DEBUG("Now len is %d", list_get_len(&model->request_list));
            lm_on_end_processing_request(model, &service, ptr_vector);
        }
        else
        {
            LOG_ERROR("%s", "Never get here");

            printf("Never get here\n");
            break;
        }
    }

    ptr_vector_free(ptr_vector);
    return OKAY;
}
