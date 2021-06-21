#ifndef __SERVICE_UNIT_H__

#define __SERVICE_UNIT_H__

#define DEF_MIN_ARRIVAL_TIME            0
#define DEF_MAX_ARRIVAL_TIME            6
#define DEF_MIN_SERVICE_TIME            0
#define DEF_MAX_SERVICE_TIME            1
#define DEF_ONE_REQUEST_CYCLE_COUNT     5
#define DEF_ENDED_REQUEST_COUNT         1000

typedef struct service_unit service_unit_t;

struct service_unit
{
    double min_arrival_time;
    double max_arrival_time;

    double min_service_time;
    double max_service_time;

    int one_request_cycle_count;
    int ended_request_count;
};

#endif // __SERVICE_UNIT_H__
