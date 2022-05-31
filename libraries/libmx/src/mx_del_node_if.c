#include "../inc/libmx.h"

void mx_del_node_if(t_list **list, void *del_data, bool (*cmp)(void *a, void *b))
{
    t_list *node = (*list)->next;
    t_list *prev = *list;

    if (node == NULL)
    {
        if (cmp(prev->data, del_data))
        {
            free(prev);
        }
        return;
    }
    
    while (node->next != NULL)
    {
        if (cmp(node->data, del_data))
        {
            prev->next = node->next;
            free(node);
            node = prev->next;
            continue;
        }

        prev = prev->next;
        node = node->next;
    }

    //last node
    if (cmp(node->data, del_data)) 
    {
        prev->next = NULL;
        free(node);
    }

    //first node
    node = *list;
    if (cmp(node->data, del_data)) 
    {
        (*list) = (*list)->next ;
        free(node);
    }
}
