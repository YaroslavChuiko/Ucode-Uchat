#include "../../inc/server.h"

t_user* mx_create_user(int id, int client_fd, SSL* ssl) {
    t_user *new_node = malloc(sizeof(t_user));
    
    new_node->user_id = id;
    new_node->client_fd = client_fd;
    new_node->name = NULL;
    new_node->password = NULL;
    new_node->ssl = ssl;
    
    new_node->next = NULL;
    return new_node;
}

void mx_user_push_back(t_user** list, int user_id, int client_fd, SSL* ssl) {

    t_user* new_node = mx_create_user(user_id, client_fd, ssl);
    if (list != NULL && *list == NULL) {
        *list = new_node;
        return;
    }

    t_user* last = *list;
    while (last->next != NULL) {
        last = last->next;
    }

    new_node->next = last->next;
    last->next = new_node;

}

t_user* mx_get_user_by_id(t_user* list, int user_id) {

    while (list) {

        if (list->user_id == user_id)
            return list;
        list = list->next;

    }
    return NULL;

}

void mx_clear_user(t_user** p) {

    if (!p || !(*p))
        return;

    free((*p)->name);
    free((*p)->password);
    free(*p);
    *p = NULL;

}

void mx_user_pop_front(t_user **head) {

    if (head == NULL || *head == NULL) return; 

    if ((*head)->next == NULL) {
        mx_clear_user(head);
        *head = NULL;
        return;
    }

    t_user* temp = *head;
    *head = (*head)->next;
    mx_clear_user(&temp);

}

void mx_user_pop_back(t_user **head) {

    if (head == NULL || *head == NULL) return;

    if ((*head)->next == NULL) {
        mx_clear_user(head);
        return;
    }

    t_user* prelast = *head;
    while (prelast->next->next != NULL) {

        prelast = prelast->next;

    }
    mx_clear_user(&prelast->next);
    prelast->next = NULL;

}

void mx_user_pop_index(t_user **list, int index) {

    int size = 0;
    t_user* head = *list;
    while (head != NULL) {
        head = head->next;
        ++size;
    }

    if (index <= 0) {
        mx_user_pop_front(list);
        return;
    } else if (index >= size) {
        mx_user_pop_back(list);
        return;
    }

    t_user* current = *list;
    for (int i = 0; current != NULL && i < (index - 1); ++i) {
        current = current->next;
    }
    t_user* next = current->next->next;
    mx_clear_user(&current->next);
    current->next = next;

}

void mx_clear_user_list(t_user **list)
{
    if (list == NULL || *list == NULL)
        return;

    t_user *node = *list;
    t_user *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        mx_clear_user(&node);
        node = next;
    }
    
    *list = NULL;
}

int mx_user_list_size(t_user* list) {

    if (list == NULL) return 0;

    t_user* head = list;
    int size = 0;
    while (head != NULL) {

        head = head->next;
        ++size;

    }
    return size;

}
