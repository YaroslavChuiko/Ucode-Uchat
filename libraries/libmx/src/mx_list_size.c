#include "../inc/libmx.h"
#include <stdio.h>

int mx_list_size(t_list* list) {

    if (list == NULL) return 0;

    t_list* head = list;
    int size = 0;
    while (head != NULL) {

        head = head->next;
        ++size;

    }
    return size;

}
