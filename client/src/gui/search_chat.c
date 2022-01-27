#include "../../inc/client.h"

void check_empty_field(GtkWidget *widget, gpointer data)
{
    char *text = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));
    if (!mx_strcmp(text, ""))
    {
        update_chatlist();
    }
}

void clear_entry_field(GtkWidget *widget, gpointer entry_field)
{
    if (widget){}
    gtk_entry_set_text(GTK_ENTRY(entry_field), "");
}

void search_field_enter_pressed(GtkWidget *widget, gpointer data)
{
    char *chat_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget)));

    int response_code = handle_join_chat_request(chat_name);
    handle_search_chat_response_code(response_code, chat_name);
}
