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
    build_rightbar_chat();
}

void update_chatlist()
{
    t_chat *chatlist = utils->chatlist;

    if (mx_chat_list_size(chatlist) == 0)
    {
        build_chatlist_message("Join to chat to start messaging");
    }
    else
    {
        GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");
        clear_container(chatlist_container);

        while (chatlist)
        {
            add_chatlist_item(chatlist->id, chatlist->name);
            chatlist = chatlist->next;
        }

        if (utils->current_chat)
        {
            set_chatlist_item_active(get_widget_by_name_r(chatlist_container, utils->current_chat->name));
        }
    }
}
