#include "../../inc/utils.h"

t_msg* mx_create_msg(int msg_id, int user_id, const char* user_name, int chat_id, const char* text, const char* date_str) {
    
    t_msg *new_node = malloc(sizeof(t_msg));
    
    new_node->message_id = msg_id;
    new_node->chat_id = chat_id;
    new_node->sender_id = user_id;
    new_node->sender_name = mx_strdup(user_name);
    new_node->text = mx_strdup(text);
    new_node->date_str = mx_strdup(date_str);
    new_node->next = NULL;
    
    return new_node;

}


void mx_msg_push_back(t_msg** list, t_msg* new_node) {

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

void mx_msg_dfl_push_back(t_msg** list, int msg_id, int user_id, const char* user_name, 
                        int chat_id, const char* text, const char* date_str) {

    t_msg* new_node = mx_create_msg(msg_id, user_id, user_name, chat_id, text, date_str);
    mx_msg_push_back(list, new_node);

}

void mx_clear_msg(t_msg** p) {

    if (!p || !(*p))
        return;

    free((*p)->sender_name);
    free((*p)->text);
    free((*p)->date_str);
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

void mx_msg_pop_id(t_msg **list, int msg_id) {

    t_msg *temp = *list;
    for (int i = 0; temp; temp = temp->next, ++i) {
        if (temp->message_id == msg_id) {
            mx_msg_pop_index(list, i);
            return;
        }
    }
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

t_msg* mx_get_last_msg_node(t_msg* list) {

    if (!list)
        return NULL;

    while (list->next) {
        list = list->next;
    }
    return list;

}

t_msg* mx_get_msg_by_id(t_msg* list, int id) {

    while (list) {

        if (list->message_id == id)
            return list;

        list = list->next;

    }
    return NULL;

}

int mx_get_msg_idx_by_id(t_msg* list, int id) {

    int i = 0;
    while (list) {

        if (list->message_id == id)
            return i;

        ++i;
        list = list->next;

    }
    return -1;

}

void mx_print_msg(t_msg* msg) {

    char str[200];
    sprintf(str, "This is a t_msg msg:\n\ttext: %s, chat_id: %d, sender_id: %d, sender_name: %s, date: %s\n", 
            msg->text, msg->chat_id, msg->sender_id, msg->sender_name, msg->date_str);
    logger(str, INFO_LOG);

}
