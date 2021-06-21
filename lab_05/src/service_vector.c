#include "../inc/service_vector.h"

double vm_get_new_arraval_time(service_unit_t *service)
{
    return random_double_in_range(service->min_arrival_time,
    service->max_arrival_time);
}

double vm_get_new_service_end_time(service_unit_t *service)
{
    return random_double_in_range(service->min_service_time,
    service->max_service_time);
}

double vm_get_curr_time(modeling_vector_t *model)
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

void vm_print_modeling_data_each_100(modeling_vector_t *model)
{
    int vector_len = queue_vector_get_len(model->request_vector);
    double avg_vector_len = model->avg_list_len;
    int avg_vector_len_count = model->avg_list_len_count;

    avg_vector_len = update_avg(avg_vector_len, avg_vector_len_count, vector_len);

    model->avg_list_len = avg_vector_len;
    model->avg_list_len_count = ++avg_vector_len_count;

    printf("Заявок покинуло ОА: %d\n", model->ended_request_count);
    printf("Заявок обработано: %d\n", model->processed_request_count);
    printf("Число заявок в очереди: %d\n", vector_len);
    printf("Среднее число заявок в очереди: %.2lf\n", model->avg_list_len);
    printf("Среднее время проведённое в очереди: %.2lf\n", model->avg_queue_time);
    printf(MESS_LINE_SEPARATOR);
}

void vm_print_whole_modeling_data(modeling_vector_t *model)
{
    printf("\n\nРезультат моделирования вектора:\n");
    printf("Количество вошедших в систему заявок: %d\n", model->created_request_count);
    printf("Количество обработанных заявок: %d\n", model->processed_request_count);
    printf("Количество покинувших систему заявок: %d\n", model->ended_request_count);
    printf("Время простоя: %.2lf\n", model->downtime);
    printf("\n");
    printf("Среднее время в очереди: %.2lf\n", model->avg_queue_time);
    printf("Длина списка заявок: %d\n", queue_vector_get_len(model->request_vector));
    printf("Средняя длина списка: %.2lf\n", model->avg_list_len);
    printf("\n");
    printf("Общее время моделирования: %.2lf е.в.\n", model->end_modeling_time);
}

bool vm_move_request_to_service(modeling_vector_t *model, service_unit_t *service)
{
    int rc;

    request_t request;
    rc =  queue_vector_pop(model->request_vector, &request);

    if (OKAY != rc)
    {
        LOG_WARNING("%s", "List is empty");
        return false;
    }

    if (!isnan(model->downtime_start))
    {
        model->downtime += vm_get_curr_time(model) - model->downtime_start;
        model->downtime_start = NAN;
    }

    model->processing_request = request;
    model->is_no_processing_request = false;

    if (0 == model->processing_request.processing_count)
    {
        model->processing_request.first_service_time = vm_get_curr_time(model);

        model->avg_queue_time = update_avg(model->avg_queue_time,
            model->avg_queue_time_count,
            model->processing_request.first_service_time -
            model->processing_request.creating_time);

        ++model->avg_queue_time_count;
    }

    model->next_service_end_time = (vm_get_curr_time(model) +
    vm_get_new_service_end_time(service));

    return true;
}

bool vm_is_time_to_exit(modeling_vector_t *model,
service_unit_t *service)
{
    bool res = service->ended_request_count == model->ended_request_count;

    LOG_TRACE("%d/%d", model->ended_request_count,
    service->ended_request_count);

    LOG_TRACE("<< %s", BOOL_TO_STR(res));

    return res;
}

void vm_on_exit(/* modeling_vector_t *model */)
{
    printf("The modeling end\n");

    LOG_INFO("%s", "The modeling end\n");
}

bool vm_is_time_to_add_new_request(modeling_vector_t *model)
{
    bool suitable_time = ((isnan(model->next_service_end_time) &&
    is_queue_vector_empty(model->request_vector)) ||
    (model->next_arrival_time <= model->next_service_end_time));

    LOG_TRACE("<< suitable_time = %s", BOOL_TO_STR(suitable_time));

    return suitable_time;
}

int vm_on_add_new_request(modeling_vector_t *model,
service_unit_t *service)
{
    int rc;

    LOG_DEBUG("model->created_request_count = %d", model->created_request_count);
    request_t new = {
        .value = model->created_request_count,
        .processing_count = 0,
        .creating_time = vm_get_curr_time(model),
        .first_service_time = NAN
    };
    ++model->created_request_count;
    rc = queue_vector_append(model->request_vector, &new);

    if (OKAY != rc)
    {
        LOG_ERROR("%s", "vector overflow");
        printf("Вектор переполнен\n");
        return VECTOR_OVERFLOW;
    }

    LOG_TRACE("%s", "New query append");

    model->next_arrival_time += vm_get_new_arraval_time(service);

    return OKAY;
}

bool vm_is_time_to_move_query_to_service(modeling_vector_t *model)
{
    bool is_service_empty = model->is_no_processing_request;
    bool is_queue_not_empty = !is_queue_vector_empty(model->request_vector);

    LOG_TRACE("is_service_empty = %s; is_queue_not_empty = %s",
    BOOL_TO_STR(is_service_empty), BOOL_TO_STR(is_queue_not_empty));

    bool res = is_service_empty && is_queue_not_empty;

    LOG_TRACE("<< %s", BOOL_TO_STR(res));

    return res;
}

void vm_on_move_queue_to_service(modeling_vector_t *model, service_unit_t *service)
{
    bool res = vm_move_request_to_service(model, service);

    assert(res);
}

bool vm_is_time_to_end_processing_request(modeling_vector_t *model)
{
    bool is_service_not_empty = !model->is_no_processing_request;
    bool is_suitable_time = (model->next_service_end_time <
    model->next_arrival_time);

    LOG_TRACE("is_service_not_empty = %s; is_suitable_time = %s",
    BOOL_TO_STR(is_service_not_empty), BOOL_TO_STR(is_suitable_time));

    bool res = is_service_not_empty && is_suitable_time;

    LOG_TRACE("<< %s", BOOL_TO_STR(res));

    return res;
}

int vm_on_end_processing_request(modeling_vector_t *model,
service_unit_t *service)
{
    int rc;

    ++model->processed_request_count;
    int count = ++model->processing_request.processing_count;

    if (count >= service->one_request_cycle_count)
    {
        LOG_TRACE("Request was in service %d times. Free them",
        service->one_request_cycle_count);

        // request_node_free(&model->processing_request);
        ++model->ended_request_count;
    }
    else
    {
        rc = queue_vector_append(model->request_vector, &model->processing_request);
        if (OKAY != rc)
        {
            LOG_ERROR("%s", "vector overflow");
            printf("Вектор переполнен");
            return VECTOR_OVERFLOW;
        }
    }

    model->is_no_processing_request = true;

    LOG_DEBUG("Now list len is %d", queue_vector_get_len(model->request_vector));

    if (is_queue_vector_empty(model->request_vector))
    {
        // model->end_modeling_time = model->next_service_end_time;
        model->downtime_start = model->next_service_end_time;
        model->next_service_end_time = NAN;
    }
    else
    {
        bool res = vm_move_request_to_service(model, service);
        LOG_TRACE("%s", BOOL_TO_STR(res));
        assert(res);
    }

    return OKAY;
}

int vector_service_modeling(modeling_vector_t *model, service_unit_t service)
{
    int rc;
    int prev_ended_request_count_for_print = 0;

    while (true)
    {
        #if LOG_LEVEL >= DEBUG_LEVEL
        print_queue_vector(stderr, model->request_vector);
        #endif

        LOG_DEBUG("@@ Next arrival time: %.5lf, next service end time: %.5lf; len: %d",
        model->next_arrival_time, model->next_service_end_time,
        queue_vector_get_len(model->request_vector));

        LOG_DEBUG("@@ Processed_request_count = %d; created_request_count = %d",
        model->processed_request_count, model->created_request_count);

        if (0 == model->ended_request_count % OUTPUT_NUMBER &&
        prev_ended_request_count_for_print  != model->ended_request_count)
        {
            vm_print_modeling_data_each_100(model);
            prev_ended_request_count_for_print = model->ended_request_count;
        }

        if (vm_is_time_to_exit(model, &service))
        {
            vm_on_exit(/* model */);
            model->end_modeling_time = vm_get_curr_time(model);
            break;
        }
        else if (vm_is_time_to_add_new_request(model))
        {
            rc = vm_on_add_new_request(model, &service);

            if (OKAY != rc)
            {
                LOG_ERROR("%s", "vector overflow");
                return VECTOR_OVERFLOW;
            }
        }
        else if (vm_is_time_to_move_query_to_service(model))
        {
            vm_on_move_queue_to_service(model, &service);
        }
        else if (vm_is_time_to_end_processing_request(model))
        {
            LOG_DEBUG("Now len is %d", queue_vector_get_len(model->request_vector));
            rc = vm_on_end_processing_request(model, &service);

            if (OKAY != rc)
            {
                LOG_ERROR("%s", "vector overflow");
                return VECTOR_OVERFLOW;
            }
        }
        else
        {
            LOG_ERROR("%s", "Never get here");

            printf("Never get here\n");
            break;
        }
    }

    return OKAY;
}
