#include "../inc/menu.h"

service_unit_t gen_default_service_unit()
{
    service_unit_t service = {
        .min_arrival_time = DEF_MIN_ARRIVAL_TIME,
        .max_arrival_time = DEF_MAX_ARRIVAL_TIME,

        .min_service_time = DEF_MIN_SERVICE_TIME,
        .max_service_time = DEF_MAX_SERVICE_TIME,

        .one_request_cycle_count = DEF_ONE_REQUEST_CYCLE_COUNT,
        .ended_request_count = DEF_ENDED_REQUEST_COUNT
    };

    return service;
}

#define OKAY                            0
#define NON_OKAY                        1
int gen_manual_servide_unit(service_unit_t *service)
{
    printf("Введите минимальный и максимальный интервал добавления элементов:\n");
    if (2 != scanf("%lf%lf", &service->min_arrival_time, &service->max_arrival_time) ||
    service->min_arrival_time > service->max_arrival_time)
    {
        printf("Неправильный ввод\n");
        return 1;
    }
    printf("Введите минимальное и максимальное время обработки:\n");
    if (2 != scanf("%lf%lf", &service->min_service_time, &service->max_service_time) ||
    service->min_service_time > service->max_service_time)
    {
        printf("Неправильный ввод\n");
        return 1;
    }
    printf("Введите число циклических обработок: \n");
    if (1 != scanf("%d", &service->one_request_cycle_count) || 0 >service->one_request_cycle_count)
    {
        printf("Неправильный ввод\n");
        return 1;
    }
    printf("Введите количество выполненных запросов для выхода: \n");
    if (1 != scanf("%d", &service->ended_request_count) || 0 > service->ended_request_count)
    {
        printf("Неправильный ввод\n");
        return 1;
    }

    return OKAY;
}

void on_default_menu_case()
{
    service_unit_t service = gen_default_service_unit();
    run_services_modeling(service);
}

int on_manual_menu_case()
{
    service_unit_t service = gen_default_service_unit();
    int rc = gen_manual_servide_unit(&service);
    if (OKAY != rc)
        return NON_OKAY;
    run_services_modeling(service);
    return OKAY;
}

int run_menu()
{
    printf(MENU_MESS);

    int menu_choice;

    if (1 != scanf("%d", &menu_choice))
    {
        printf("Некорректный ввод\n");
        return 1;
    }

    switch (menu_choice)
    {
        case 0:
            printf("Выход\n");
            break;
        case 1:
            on_default_menu_case();
            break;
        case 2:
            on_manual_menu_case();
            break;
        case 3:
            on_stat_menu_case();
            break;
        default:
            printf("Некорректный ввод\n");
            return 1;
    }

    return OKAY;
}
