#ifndef __SERVICE_VECTOR_H__

#define __SERVICE_VECTOR_H__

#include <math.h>

#include "request.h"
#include "random.h"

#include "queue_vector.h"

#include "defines.h"
#include "messages.h"
#include "mymath.h"
#include "service_unit.h"

#define OUTPUT_NUMBER                   100

#define OKAY                            0
#define VECTOR_OVERFLOW                 1

typedef struct modeling_vector modeling_vector_t;

struct modeling_vector
{
    queue_vector_t *request_vector;
    request_t processing_request;
    bool is_no_processing_request;

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

    double downtime;
    double downtime_start;
};

void vm_print_whole_modeling_data(modeling_vector_t *model);

int vector_service_modeling(modeling_vector_t *model, service_unit_t service);

#endif // __SERVICE_VECTOR_H__
