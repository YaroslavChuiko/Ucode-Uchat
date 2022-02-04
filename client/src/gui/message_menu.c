#include "../../inc/client.h"

void delete_message(GtkWidget *widget, GdkEventButton *event, t_msg *message) {
    if(widget){};

    handle_delete_msg_request(message->message_id);
    update_chat_field();
}

void edit_button_click(GtkWidget *widget, t_msg *message) {
    if(widget){};

    GtkWidget *new_message_field = get_widget_by_name_r(main_window, "new_message_field");
    GtkWidget *send_btn = get_widget_by_name_r(main_window, "send_btn");
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");

    gchar new_message[2048];
    sprintf(new_message, "%s", gtk_entry_get_text(GTK_ENTRY(new_message_field)));
    if (!new_message[0]) {
        delete_message(NULL, NULL, message);
        return;
    }

    gtk_entry_set_text(GTK_ENTRY(new_message_field), "");
    g_signal_handler_unblock(send_btn, g_signal_handler_find(send_btn, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));
    g_signal_handler_disconnect(send_btn, g_signal_handler_find(send_btn, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)edit_button_click, NULL)); 
    g_signal_handler_disconnect(new_message_field, g_signal_handler_find(new_message_field, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)edit_button_click, NULL)); 
    g_signal_handler_unblock(new_message_field, g_signal_handler_find(new_message_field, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));

    handle_edit_msg_request(message->message_id, new_message);

    update_chat_field();

    gtk_widget_show_all(chat_container);
}

void edit_message(GtkWidget *widget, GdkEventButton *event, t_msg *message) {
    if(widget){};

    GtkWidget *new_message_field = get_widget_by_name_r(main_window, "new_message_field");
    GtkWidget *send_btn = get_widget_by_name_r(main_window, "send_btn");

    gtk_entry_set_text(GTK_ENTRY(new_message_field), message->text);

    g_signal_handler_block(widget, g_signal_handler_find(widget, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)edit_message, NULL));

    g_signal_handler_block(send_btn, g_signal_handler_find(send_btn, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));
    g_signal_handler_block(new_message_field, g_signal_handler_find(new_message_field, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));
    g_signal_connect(new_message_field, "activate", G_CALLBACK(edit_button_click), message);
    g_signal_connect(send_btn, "clicked", G_CALLBACK(edit_button_click), message); 
    gtk_button_set_label(GTK_BUTTON(send_btn), "E");    
}

