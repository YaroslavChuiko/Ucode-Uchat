#include "../../inc/client.h"

void scroll_to_end(GtkWidget *widget, gpointer data) {
    GtkWidget *scrollable_wrap = get_widget_by_name_r(main_window, "scrollable_wrap");
    GtkWidget *chat_field = get_widget_by_name_r(main_window, "chat_field");

    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrollable_wrap));
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble page_size = gtk_adjustment_get_page_size(adj);
    gtk_adjustment_set_value(adj, upper - page_size);

    gtk_widget_show_all(chat_field);
}

void send_button_click(GtkWidget *widget, gpointer new_message_field) {
    if(widget){};

    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");
    GtkWidget *chat_field = get_widget_by_name_r(chat_container, "chat_field");
    GtkWidget *messaging_label = get_widget_by_name_r(chat_container, "messaging_label");

    gchar new_message[2048];
    sprintf(new_message, "%s", gtk_entry_get_text(new_message_field));
    if (!new_message[0]) {
        return;
    }

    if (messaging_label) {
        gtk_widget_destroy(messaging_label);
        messaging_label = gtk_label_new("No messages here yet...");
    }

    gtk_entry_set_text(new_message_field, "");

    if (handle_send_msg_request(new_message) == R_SUCCESS) {

        add_message(mx_get_last_msg_node(utils->current_chat->messages));

        // gtk_widget_show_all(chat_container);
    
    }

}

void build_rightbar_chat() {
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");

    gtk_container_foreach(GTK_CONTAINER(chat_container), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *chat_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(chat_header, TRUE);
    add_class(chat_header, "chatlist_item");

    GtkWidget *avatar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chat_header), avatar, FALSE, FALSE, 0);
    add_class(avatar, "chatlist_item_avatar");

    GtkWidget *chat_header_text = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chat_header_text), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chat_header_text), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chat_header), chat_header_text, false, false, 0);
    add_class(chat_header_text, "chatlist_item_text");

    GtkWidget *chat_header_title = gtk_label_new(utils->current_chat->name);
    gtk_widget_set_halign(GTK_WIDGET(chat_header_title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chat_header_text), chat_header_title, false, false, 0);
    GtkWidget *chat_header_time = gtk_label_new("Online");
    gtk_widget_set_halign(GTK_WIDGET(chat_header_time), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chat_header_text), chat_header_time, false, false, 0);

    if (utils->current_chat->permissions == ADMIN_MEMBER)
    {
        GtkWidget *delete_chat_btn = gtk_event_box_new();
        add_class(delete_chat_btn, "event_switch_auth_menu");
        gtk_widget_set_halign(GTK_WIDGET(delete_chat_btn), GTK_ALIGN_CENTER);
        g_signal_connect(G_OBJECT(delete_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(delete_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(delete_chat_btn), "button_press_event", G_CALLBACK(delete_chat_btn_click), NULL);
        GtkWidget *delete_chat_label = gtk_label_new("Delete chat");
        add_class(delete_chat_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(delete_chat_btn), delete_chat_label);
        gtk_box_pack_end(GTK_BOX(chat_header), delete_chat_btn, FALSE, FALSE, 0);
    }

    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrollable_wrap, "scrollable_wrap");

    GtkWidget *chat_field = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(chat_field, "chat_field");
    gtk_widget_set_hexpand(chat_field, TRUE);
    add_class(chat_field, "chat");
    gtk_widget_set_events(chat_field, GDK_ALL_EVENTS_MASK);
    g_signal_connect(chat_field, "size-allocate", G_CALLBACK(scroll_to_end), NULL);
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chat_field);

    GtkWidget *message_field = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(message_field, "message_field");
    gtk_widget_set_halign(GTK_WIDGET(message_field), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(message_field), GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(message_field, TRUE);
    gtk_box_pack_end(GTK_BOX(chat_container), message_field, false, false, 0);

    GtkWidget *new_message_field = gtk_entry_new();
    gtk_widget_set_name(new_message_field, "new_message_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_message_field), "Message");
    gtk_widget_set_halign(GTK_WIDGET(new_message_field), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(new_message_field), GTK_ALIGN_FILL);
    g_signal_connect(new_message_field, "activate", G_CALLBACK(send_button_click), new_message_field);
    gtk_box_pack_start(GTK_BOX(message_field), new_message_field, TRUE, TRUE, 0);

    GtkWidget *send_btn = gtk_button_new_with_label("S");
    gtk_widget_set_name(send_btn, "send_btn");
    g_signal_connect(send_btn, "clicked", G_CALLBACK(send_button_click), new_message_field);
    gtk_widget_set_halign(GTK_WIDGET(send_btn), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(send_btn), GTK_ALIGN_END);

    gtk_box_pack_start(GTK_BOX(chat_container), chat_header, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_container), scrollable_wrap, true, true, 0);
    gtk_box_pack_start(GTK_BOX(message_field), send_btn, FALSE, FALSE, 0);

    update_chat_field();

    gtk_widget_show_all(chat_container);
}

