#include "../inc/libmx.h"

void mx_print_list(t_list* list) {

    while (list) {

        mx_printstr(list->data);
        mx_printstr("\n");
        list = list->next;

    }

}
