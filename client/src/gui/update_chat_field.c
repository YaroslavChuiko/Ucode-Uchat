#include "../../inc/client.h"

void add_message(t_msg *message) {
    GtkWidget *chat_field = get_widget_by_name_r(main_window, "chat_field");

    int cur_user = message->sender_id == utils->current_user->user_id ? 1 : 0;

    GtkWidget *message_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_halign(GTK_WIDGET(message_box), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(message_box), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START);
    gtk_widget_set_hexpand(message_box, TRUE);
    add_class(message_box, "msg_box");
    gtk_box_pack_start(GTK_BOX(chat_field), message_box, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 27, 27);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_user_avatar), (gpointer)message->avatar_color);
    gtk_widget_set_halign(avatar, cur_user ? GTK_ALIGN_START : GTK_ALIGN_END);
    gtk_widget_set_valign(avatar, GTK_ALIGN_START);
    if (!cur_user) {
        gtk_box_pack_start(GTK_BOX(message_box), avatar, FALSE, FALSE, 0);
    }

    GtkWidget *message_text = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(GTK_WIDGET(message_text), cur_user ? GTK_ALIGN_START : GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(message_text), cur_user ? GTK_ALIGN_START : GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(message_box), message_text, false, false, 0);
    add_class(message_text, "msg_text");

    GtkWidget *message_head = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(message_text), message_head, false, false, 0);
    add_class(message_head, "msg_head");

    GtkWidget *delete_btn = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(delete_btn), 20, 16);
	add_class(delete_btn, "delete_msg_btn");
	g_signal_connect(G_OBJECT(delete_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(delete_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
	g_signal_connect(G_OBJECT(delete_btn), "button_press_event", G_CALLBACK(delete_message), message);

	if (cur_user) {
        gtk_box_pack_start(GTK_BOX(message_head), delete_btn, FALSE, FALSE, 0);
    }
    else {
        gtk_box_pack_end(GTK_BOX(message_head), delete_btn, FALSE, FALSE, 0);
    }

    if (cur_user) {
        GtkWidget *edit_btn = gtk_event_box_new();
        gtk_widget_set_size_request(GTK_WIDGET(edit_btn), 20, 16);
        add_class(edit_btn, "edit_msg_btn");
        g_signal_connect(G_OBJECT(edit_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(edit_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(edit_btn), "button_press_event", G_CALLBACK(edit_message), message);
        gtk_box_pack_start(GTK_BOX(message_head), edit_btn, FALSE, FALSE, 0);
    }

    GtkWidget *user_name = gtk_label_new(message->sender_name);
    add_class(user_name, "msg_name");
    if (cur_user) {
        add_class(user_name, "msg_name--right");
        gtk_box_pack_end(GTK_BOX(message_head), user_name, false, false, 0);
    }
    else {
        add_class(user_name, "msg_name--left");
        gtk_box_pack_start(GTK_BOX(message_head), user_name, false, false, 0);
    }
    
    GtkWidget *sent_message = gtk_label_new(message->text);
    gtk_widget_set_halign(GTK_WIDGET(sent_message), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START);
    ////
    gtk_label_set_selectable(GTK_LABEL(sent_message), TRUE);
    gtk_label_set_single_line_mode(GTK_LABEL(sent_message), FALSE);
    gtk_label_set_max_width_chars(GTK_LABEL(sent_message), 50);
    gtk_label_set_line_wrap(GTK_LABEL(sent_message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(sent_message), PANGO_WRAP_WORD);
    /////
    gtk_box_pack_start(GTK_BOX(message_text), sent_message, false, false, 0);
    add_class(sent_message, cur_user ? "right_message" : "left_message");

    GtkWidget *message_time = gtk_label_new(message->date_str); 
    add_class(message_time, "msg_time");
    gtk_widget_set_halign(GTK_WIDGET(message_time), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(message_text), message_time, false, false, 0);

    if (cur_user) {
        gtk_box_pack_start(GTK_BOX(message_box), avatar, FALSE, FALSE, 0);
    }

    gtk_widget_show_all(chat_field);
}

void update_chat_field() {
    GtkWidget *chat_field = get_widget_by_name_r(main_window, "chat_field");

    clear_container(chat_field);

    t_msg *messages = utils->current_chat->messages;
    if (mx_msg_list_size(messages) == 0) {
        GtkWidget *messaging_label = gtk_label_new("No messages here yet...");
        gtk_widget_set_name(messaging_label, "messaging_label");
        gtk_widget_set_halign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
        gtk_widget_set_valign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
        gtk_widget_set_vexpand(messaging_label, TRUE);
        gtk_widget_set_hexpand(messaging_label, TRUE);
        gtk_box_pack_start(GTK_BOX(chat_field), messaging_label, FALSE, FALSE, 0);
    }
    else {
        while (messages) {
            add_message(messages);
            messages = messages->next;
        }
    }
    
    gtk_widget_show_all(chat_field);
}
