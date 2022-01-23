#include "../../inc/utils.h"

t_msg* mx_create_msg(int user_id, const char* user_name, int chat_id, const char* text/*, int date*/) {
    
    t_msg *new_node = malloc(sizeof(t_msg));
    
    new_node->chat_id = chat_id;
    new_node->sender_id = user_id;
    new_node->sender_name = strdup(user_name);
    new_node->text = strdup(text);
    // new_node->date = date;
    new_node->next = NULL;
    
    return new_node;

}

void mx_msg_push_back(t_msg** list, int user_id, const char* user_name, int chat_id, const char* text/*, int date*/) {

    t_msg* new_node = mx_create_msg(user_id, user_name, chat_id, text/*, date*/);
    if (list != NULL && *list == NULL) {
        *list = new_node;
        return;
    }

    t_msg* last = *list;
    while (last->next != NULL) {
        last = last->next;
    }

    new_node->next = last->next;
    last->next = new_node;

}

void mx_clear_msg(t_msg** p) {

    if (!p || !(*p))
        return;

    free((*p)->sender_name);
    free((*p)->text);
    free(*p);
    *p = NULL;

}

void mx_msg_pop_front(t_msg **head) {

    if (head == NULL || *head == NULL) return; 

    if ((*head)->next == NULL) {
        mx_clear_msg(head);
        *head = NULL;
        return;
    }

    t_msg* temp = *head;
    *head = (*head)->next;
    mx_clear_msg(&temp);

}

void mx_msg_pop_back(t_msg **head) {

    if (head == NULL || *head == NULL) return;

    if ((*head)->next == NULL) {
        mx_clear_msg(head);
        return;
    }

    t_msg* prelast = *head;
    while (prelast->next->next != NULL) {

        prelast = prelast->next;

    }
    mx_clear_msg(&prelast->next);
    prelast->next = NULL;

}

void mx_msg_pop_index(t_msg **list, int index) {

    int size = 0;
    t_msg* head = *list;
    while (head != NULL) {
        head = head->next;
        ++size;
    }

    if (index <= 0) {
        mx_msg_pop_front(list);
        return;
    } else if (index >= size) {
        mx_msg_pop_back(list);
        return;
    }

    t_msg* current = *list;
    for (int i = 0; current != NULL && i < (index - 1); ++i) {
        current = current->next;
    }
    t_msg* next = current->next->next;
    mx_clear_msg(&current->next);
    current->next = next;

}

void mx_clear_msg_list(t_msg **list)
{
    if (list == NULL || *list == NULL)
        return;

    t_msg *node = *list;
    t_msg *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        mx_clear_msg(&node);
        node = next;
    }
    
    *list = NULL;
}

int mx_msg_list_size(t_msg* list) {

    if (list == NULL) return 0;

    t_msg* head = list;
    int size = 0;
    while (head != NULL) {

        head = head->next;
        ++size;

    }
    return size;

}
