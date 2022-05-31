#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *a, void *b)) {

    if (lst == NULL) return NULL;

    t_list* current = lst;
    while (current != NULL) {
 
        t_list* next_node = current->next;
        while (next_node != NULL) {

            if (cmp(current->data, next_node->data)) {

                t_list* temp = current->data;
                current->data = next_node->data;
                next_node->data = temp;

            }
            next_node = next_node->next;

        }
        current = current->next;

    }
    return lst;

}
