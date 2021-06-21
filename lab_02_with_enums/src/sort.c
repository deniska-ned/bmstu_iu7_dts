#include "../inc/sort.h"

int comp_countries(const void *ptr_country_1, const void *ptr_country_2)
{
    country_t country_1 = *((const country_t *) ptr_country_1);
    country_t country_2 = *((const country_t *) ptr_country_2);

    return strcmp(country_1.name, country_2.name);
}

int comp_keys(const void *ptr_key_1, const void *ptr_key_2)
{
    key_name_t key_1 = *((const key_name_t *) ptr_key_1);
    key_name_t key_2 = *((const key_name_t *) ptr_key_2);

    return strcmp(key_1.name, key_2.name);
}

void selection_sort(void *ptr, size_t count, size_t size,
int (*comp)(const void *, const void *))
{
    if (0 == count)
    {
        LOG_INFO("%s", "0 len array sorted");
        return;
    }

    for (size_t i = count - 1; i >= 1; --i)
    {
        size_t max_v_i = 0;
        for (size_t j = 1; j <= i; ++j)
        {
            void *p_cur_elem = (char *) ptr + j * size;
            void *p_max_elem = (char *) ptr + max_v_i * size;

            if (comp(p_cur_elem, p_max_elem) > 0)
                max_v_i = j;
        }
        SWAP((char *) ptr + max_v_i * size, (char *) ptr + i * size, size);
    }

    LOG_INFO("%zu len array sorted", count);
    return;
}
