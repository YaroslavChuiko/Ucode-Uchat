#include "../../inc/client.h"

static int get_chatlist_item_id(GtkWidget *chatlist_item)
{
    int id;
    GtkWidget *id_label = get_widget_by_name_r(chatlist_item, "chat_id");
    id = mx_atoi((char*)gtk_label_get_text(GTK_LABEL(id_label)));

    return id;
}

void set_current_chat(GtkWidget *chatlist_item)
{
    int chat_id = get_chatlist_item_id(chatlist_item);
    utils->current_chat = mx_get_chat_by_id(utils->chatlist, chat_id);
}

void set_chatlist_item_active(GtkWidget *widget)
{
    GtkWidget *chatlist_container = gtk_widget_get_parent(widget);

    GList *children = gtk_container_get_children(GTK_CONTAINER(chatlist_container));
    while (children)
    {
        remove_class(GTK_WIDGET(children->data), "active");
        children = children->next;
    }
    g_list_free(g_steal_pointer(&children));
    
    // gtk_container_foreach(GTK_CONTAINER(chatlist_container), (GtkCallback)remove_class, "active");
    add_class(widget, "active");
}

void clicked_chatlist_item(GtkWidget *widget, gpointer data)
{
    set_current_chat(widget);
    set_chatlist_item_active(widget);
    // build_delete_chat_btn();
}

void update_chatlist()
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");
    // int id;

    // if (utils->current_chat)
    // {
    //     id = utils->current_chat->id;
    // }
    
    // if(handle_get_chats_request() == R_SUCCESS)
    // {
        // clear_chatlist();
        clear_container(chatlist_container);

        t_chat *chatlist = utils->chatlist;
        if (mx_chat_list_size(chatlist) == 0)
        {
            buid_chatlist_message("Join to chat to start messaging");
        }
        else
        {
            while (chatlist)
            {
                add_chatlist_item(chatlist->id, chatlist->name);
                chatlist = chatlist->next;
            }

            // utils->current_chat = mx_get_chat_by_id(utils->chatlist, id);
            if (utils->current_chat)
            {
                set_chatlist_item_active(get_widget_by_name_r(chatlist_container, utils->current_chat->name));
                // set_chatlist_item_active(get_widget_by_name_r(chatlist_container, mx_itoa(utils->current_chat->id)));
            }
        }
    // }
}
