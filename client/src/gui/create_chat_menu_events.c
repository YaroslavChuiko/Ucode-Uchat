#include "../../inc/client.h"

void popup_create_chat_menu(GtkWidget *widget, gpointer chat_screen)
{
    if(widget){}
    (void)chat_screen;

    build_create_chat_menu();
}

void create_chat_btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    (void)data;
    GtkWidget *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    GtkWidget *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");

    if (!validate_name_field(chat_name_field, chat_name_notify_label))
    {
        return;
    }
    
    char *group_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(chat_name_field)));

    int response_code = handle_create_chat_request(group_name);
    handle_create_chat_response_code(response_code, chat_name_field, chat_name_notify_label);
}
