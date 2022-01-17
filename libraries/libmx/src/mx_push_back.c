#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {

    t_list* new_node = mx_create_node(data);
    if (list != NULL && *list == NULL) {
        *list = new_node;
        return;
    }

    t_list* last = *list;
    while (last->next != NULL) {
        last = last->next;
    } 

    new_node->next = last->next;
    last->next = new_node;

}
