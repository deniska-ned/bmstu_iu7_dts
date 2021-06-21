#ifndef __SERVICES_H__

#define __SERVICES_H__

#include "service_list.h"
#include "service_vector.h"
#include "timer.h"
#include "stat.h"

#define DEF_ARRAY_LEN                   10000

void run_services_modeling(service_unit_t service);

#endif // __SERVICES_H__
