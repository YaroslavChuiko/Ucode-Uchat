#include "../../inc/client.h"

static void build_found_chats(t_chat *chat_list)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");

    if (!chat_list)
    {
        build_chatlist_message(get_response_str(R_CHAT_NOENT));
    }
    else
    {
        clear_container(chatlist_container);

        while (chat_list)
        {
            add_join_chat_item(chat_list->id, chat_list->name);
            chat_list = chat_list->next;
        }
    }
}

static void update_found_chats(char *search_str)
{
    t_chat *chat_list = handle_search_chats_request(search_str);
    build_found_chats(chat_list);
}

void search_field_change_event(GtkWidget *widget, gpointer data)
{
    char *search_str = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
    if (!mx_strcmp(search_str, ""))
    {
        update_chatlist();
    }
    else
    {
        update_found_chats(search_str);
    }
    (void)data;
}

void clear_search_field(GtkWidget *widget, gpointer entry_field)
{
    if (widget){}
    gtk_entry_set_text(GTK_ENTRY(entry_field), "");
}
