#ifndef __REQUEST_H__

#define __REQUEST_H__

typedef struct request request_t;

struct request
{
    int value;
    int processing_count;
    double creating_time;
    double first_service_time;
};

#endif // __REQUEST_H__
