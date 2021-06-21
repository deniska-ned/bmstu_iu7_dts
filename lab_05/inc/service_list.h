#ifndef __SERVICE_LIST_H__

#define __SERVICE_LIST_H__

#include <math.h>

#include "request.h"
#include "random.h"

#include "queue_list.h"

#include "defines.h"
#include "messages.h"
#include "mymath.h"
#include "service_unit.h"

#include "ptr_vector.h"

#define OKAY                            0
#define DEFAULT_PTR_VECTOR_LEN          50
#define OUTPUT_NUMBER                   100

typedef struct modeling_list modeling_list_t;

struct modeling_list
{
    list_t request_list;
    request_node_t *processing_request;

    int created_request_count;
    int processed_request_count;
    int ended_request_count;

    double next_arrival_time;
    double next_service_end_time;

    double avg_list_len;
    int avg_list_len_count;

    double avg_queue_time;
    int avg_queue_time_count;

    double end_modeling_time;

    size_t ptr_vector_used_len;

    double downtime;
    double downtime_start;
};

void lm_print_whole_modeling_data(modeling_list_t *model);

int list_service_modeling(modeling_list_t *model, service_unit_t service);

#endif // __SERVICE_LIST_H__
