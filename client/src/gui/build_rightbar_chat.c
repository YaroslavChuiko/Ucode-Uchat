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

    printf("%s\n", new_message);

    if (handle_send_msg_request(new_message) == R_SUCCESS) {

        add_message(mx_get_last_msg_node(utils->current_chat->messages));

        //gtk_widget_show_all(chat_container);
    
    }

}

void build_rightbar_chat() {
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");

    gtk_container_foreach(GTK_CONTAINER(chat_container), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *chat_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(chat_header, TRUE);
    add_class(chat_header, "chat_header");

    GtkWidget *avatar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chat_header), avatar, FALSE, FALSE, 0);
    add_class(avatar, "chatlist_item_avatar");

    GtkWidget *chat_header_title = gtk_label_new(utils->current_chat->name);
    gtk_widget_set_name(chat_header_title, "chat_header_title");
    gtk_widget_set_halign(GTK_WIDGET(chat_header_title), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chat_header_title), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chat_header), chat_header_title, false, false, 0);
    add_class(chat_header_title, "chat_title");

    if (utils->current_chat->permissions == ADMIN_MEMBER)
    {
        GtkWidget *delete_chat_btn = gtk_event_box_new();
        add_class(delete_chat_btn, "event_switch_auth_menu");
        gtk_widget_set_halign(GTK_WIDGET(delete_chat_btn), GTK_ALIGN_CENTER);
        g_signal_connect(G_OBJECT(delete_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(delete_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(delete_chat_btn), "button_press_event", G_CALLBACK(build_confirm_delete_chat_window), NULL);
        GtkWidget *delete_chat_label = gtk_label_new("Delete chat");
        add_class(delete_chat_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(delete_chat_btn), delete_chat_label);
        gtk_box_pack_end(GTK_BOX(chat_header), delete_chat_btn, FALSE, FALSE, 0);
    }
    else {
        GtkWidget *leave_chat_btn = gtk_event_box_new();
        add_class(leave_chat_btn, "event_switch_auth_menu");
        gtk_widget_set_halign(GTK_WIDGET(leave_chat_btn), GTK_ALIGN_CENTER);
        g_signal_connect(G_OBJECT(leave_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(leave_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(leave_chat_btn), "button_press_event", G_CALLBACK(build_confirm_leave_chat_window), NULL);
        GtkWidget *leave_chat_label = gtk_label_new("Leave chat");
        add_class(leave_chat_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(leave_chat_btn), leave_chat_label);
        gtk_box_pack_end(GTK_BOX(chat_header), leave_chat_btn, FALSE, FALSE, 0);
    }

    GtkWidget *change_chat_name_btn = gtk_event_box_new();
    add_class(change_chat_name_btn, "event_switch_auth_menu");
    gtk_widget_set_halign(GTK_WIDGET(change_chat_name_btn), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "button_press_event", G_CALLBACK(build_change_chat_name_window), NULL);
    GtkWidget *change_chat_name_label = gtk_label_new("Change chat name");
    add_class(change_chat_name_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(change_chat_name_btn), change_chat_name_label);
    gtk_box_pack_end(GTK_BOX(chat_header), change_chat_name_btn, FALSE, FALSE, 0);

    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrollable_wrap, "scrollable_wrap");

    GtkWidget *chat_field = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(chat_field, "chat_field");
    gtk_widget_set_hexpand(chat_field, TRUE);
    add_class(chat_field, "messagelist");
    gtk_widget_set_events(chat_field, GDK_ALL_EVENTS_MASK);
    g_signal_connect(chat_field, "size-allocate", G_CALLBACK(scroll_to_end), NULL);
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chat_field);

    GtkWidget *message_field = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(message_field, "message_field");
    add_class(message_field, "input-msg_box");
    gtk_widget_set_halign(GTK_WIDGET(message_field), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(message_field), GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(message_field, TRUE);
    gtk_box_pack_end(GTK_BOX(chat_container), message_field, false, false, 0);

    GtkWidget *new_message_field = gtk_entry_new();
    gtk_widget_set_name(new_message_field, "new_message_field");
    add_class(new_message_field, "input-msg_entry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_message_field), "Message");
    gtk_widget_set_halign(GTK_WIDGET(new_message_field), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(new_message_field), GTK_ALIGN_FILL);
    gtk_entry_set_max_length(GTK_ENTRY(new_message_field), 100);
    g_signal_connect(new_message_field, "activate", G_CALLBACK(send_button_click), new_message_field);
    gtk_box_pack_start(GTK_BOX(message_field), new_message_field, TRUE, TRUE, 0);

    GtkWidget *send_btn = gtk_button_new();
    gtk_widget_set_size_request(GTK_WIDGET(send_btn), 55, 55);
    gtk_widget_set_name(send_btn, "send_btn");
    add_class(send_btn, "input-msg_send-btn");
    g_signal_connect(send_btn, "clicked", G_CALLBACK(send_button_click), new_message_field);
    gtk_widget_set_halign(GTK_WIDGET(send_btn), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(send_btn), GTK_ALIGN_END);

    gtk_box_pack_start(GTK_BOX(chat_container), chat_header, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_container), scrollable_wrap, true, true, 0);
    gtk_box_pack_start(GTK_BOX(message_field), send_btn, FALSE, FALSE, 0);

    update_chat_field();

    gtk_widget_show_all(chat_container);
}

