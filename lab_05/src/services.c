#include "../inc/services.h"

modeling_list_t list_model_init()
{
    modeling_list_t list_model = {
        .request_list = list_init(),
        .processing_request = NULL,

        .created_request_count = 0,
        .processed_request_count = 0,
        .ended_request_count = 0,

        .next_arrival_time = 0.0,
        .next_service_end_time = 0.0,

        .avg_list_len = 0.0,
        .avg_list_len_count = 0,

        .avg_queue_time = 0.0,
        .avg_queue_time_count = 0,

        .end_modeling_time = 0.0,

        .ptr_vector_used_len = 0,

        .downtime = 0.0,
        .downtime_start = NAN
    };

    return list_model;
}

modeling_vector_t vector_model_init()
{
    modeling_vector_t model = {
        .request_vector = queue_vector_allocate(DEF_ARRAY_LEN),
        // .processing_request,
        .is_no_processing_request = true,

        .created_request_count = 0,
        .processed_request_count = 0,
        .ended_request_count = 0,

        .next_arrival_time = 0.0,
        .next_service_end_time = 0.0,

        .avg_list_len = 0.0,
        .avg_list_len_count = 0,

        .avg_queue_time = 0.0,
        .avg_queue_time_count = 0,

        .end_modeling_time = 0.0,

        .downtime = 0.0,
        .downtime_start = NAN
    };

    return model;
}

void run_services_modeling(service_unit_t service)
{
    int rc;
    uint64_t slmt, elmt, svmt, evmt;

    slmt = curr_ticks();
    modeling_list_t list_model = list_model_init();
    list_service_modeling(&list_model, service);
    elmt = curr_ticks();

    printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");

    svmt = curr_ticks();
    modeling_vector_t vector_model = vector_model_init();
    rc = vector_service_modeling(&vector_model, service);
    if (OKAY != rc)
    {
        printf(MESS_ALLOCATION_ERROR);
        return;
    }
    evmt = curr_ticks();

    lm_print_whole_modeling_data(&list_model);

    printf("Реальное время моделирования: %"PRId64"\n", elmt - slmt);

    printf(MESS_LINE_SEPARATOR);

    vm_print_whole_modeling_data(&vector_model);

    printf("Реальное время моделирования: %"PRId64"\n", evmt - svmt);
    printf(MESS_LINE_SEPARATOR);
    
    // print_expected_results(service);
    modeling_stat_print(&list_model, &vector_model, &service);
}
