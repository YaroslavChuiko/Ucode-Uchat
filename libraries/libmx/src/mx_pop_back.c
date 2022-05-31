#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {

    if (head == NULL || *head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    t_list* prelast = *head;
    while (prelast->next->next != NULL) {

        prelast = prelast->next;

    }
    free(prelast->next);
    prelast->next = NULL;

}
