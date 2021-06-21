#include "../inc/list.h"
#include "../inc/vector.h"
#include "../inc/stack_vector.h"

#include "../inc/menu.h"
#include "../inc/first_alloc.h"
#include "../inc/errors.h"

int main(void)
{
    int rc;

    vector_t *adress_vector;
    stack_vector_t *stack_vector;
    list_item_t *stack_list_head;

    rc = first_allocation(&stack_vector, &stack_list_head, &adress_vector);

    if (OKAY != rc)
    {
        LOG_ERROR("%s", "First allocaton failed");
        return FIRST_ALLOCATION_FAILED;
    }

    rc = menu_start(&stack_vector, &stack_list_head, &adress_vector);

    end_free(&stack_vector, &stack_list_head, &adress_vector);

    return rc;
}
