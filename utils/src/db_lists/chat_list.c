#include "../../inc/utils.h"

t_chat *mx_create_chat(int id, const char* name, int permissions, int chat_color) {
    
    t_chat *new_node = malloc(sizeof(t_chat));
    
    new_node->id = id;
    new_node->name = name ? mx_strdup(name) : NULL;
    new_node->permissions = permissions;
    new_node->avatar_color = chat_color;
    new_node->new_msg_count = 0;
    new_node->messages = NULL;
    new_node->new_messages = NULL;
    new_node->last_new_msg = NULL;
    new_node->next = NULL;
    return new_node;
}

void mx_chat_push_back(t_chat** list, int chat_id, const char* name, int permissions, int chat_color) {

    t_chat* new_node = mx_create_chat(chat_id, name, permissions, chat_color);
    if (list != NULL && *list == NULL) {
        *list = new_node;
        return;
    }

    t_chat* last = *list;
    while (last->next != NULL) {
        last = last->next;
    }

    new_node->next = last->next;
    last->next = new_node;

}

t_chat* mx_get_chat_by_id(t_chat* list, int chat_id) {

    while (list) {

        if (list->id == chat_id)    
            return list;

        list = list->next;

    }
    return NULL;

}

t_chat* mx_get_chat_by_name(t_chat* list, const char* name) {

    while (list) {

        if (mx_strcmp(list->name, name) == 0)
            return list;

        list = list->next;

    }
    return NULL;

}

void mx_clear_chat(t_chat** p) {

    if (!p || !(*p))
        return;

    if ((*p)->name)
        free((*p)->name);
    
    free(*p);
    *p = NULL;

}

void mx_chat_pop_front(t_chat **head) {

    if (head == NULL || *head == NULL) return; 

    if ((*head)->next == NULL) {
        mx_clear_chat(head);
        *head = NULL;
        return;
    }

    t_chat* temp = *head;
    *head = (*head)->next;
    mx_clear_chat(&temp);

}

void mx_chat_pop_back(t_chat **head) {

    if (head == NULL || *head == NULL) return;

    if ((*head)->next == NULL) {
        mx_clear_chat(head);
        return;
    }

    t_chat* prelast = *head;
    while (prelast->next->next != NULL) {

        prelast = prelast->next;

    }
    mx_clear_chat(&prelast->next);
    prelast->next = NULL;

}

void mx_chat_pop_id(t_chat **list, int chat_id) {

    t_chat *temp = *list;
    for (int i = 0; temp; temp = temp->next, ++i) {
        if (temp->id == chat_id) {
            mx_chat_pop_index(list, i);
            return;
        }
    }
    return;
}

void mx_chat_pop_index(t_chat **list, int index) {

    int size = 0;
    t_chat* head = *list;
    while (head != NULL) {
        head = head->next;
        ++size;
    }

    if (index <= 0) {
        mx_chat_pop_front(list);
        return;
    } else if (index >= size) {
        mx_chat_pop_back(list);
        return;
    }

    t_chat* current = *list;
    for (int i = 0; current != NULL && i < (index - 1); ++i) {
        current = current->next;
    }
    t_chat* next = current->next->next;
    mx_clear_chat(&current->next);
    current->next = next;

}

void mx_clear_chat_list(t_chat **list)
{
    if (list == NULL || *list == NULL)
        return;

    t_chat *node = *list;
    t_chat *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        mx_clear_msg_list(&node->messages);
        mx_clear_msg_list(&node->new_messages);
        mx_clear_chat(&node);
        node = next;
    }
    
    *list = NULL;
}

int mx_chat_list_size(t_chat* list) {

    if (list == NULL) return 0;

    t_chat* head = list;
    int size = 0;
    while (head != NULL) {

        head = head->next;
        ++size;

    }
    return size;

}

int mx_get_last_msg_id(t_chat* chat) {

    if (!chat || !chat->messages) 
        return 0;

    t_msg* current = chat->messages;
    while (current->next) {
        
        current = current->next;

    }
    return current ? current->message_id : 0;

}
