#ifndef __STAT_H__

#define __STAT_H__

#include <stdio.h>
#include <math.h>

#include "../inc/timer.h"
#include "../inc/queue_list.h"
#include "../inc/queue_vector.h"
#include "../inc/service_list.h"
#include "../inc/service_vector.h"

void on_stat_menu_case();

void print_expected_results(service_unit_t service);

void modeling_stat_print(modeling_list_t *lmodel, modeling_vector_t *vmodel,
service_unit_t *service);

#endif // __STAT_H__
