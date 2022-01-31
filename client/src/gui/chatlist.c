#include "../../inc/client.h"

void add_chatlist_item(int id, char *chat_name)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");

    GtkWidget *event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(chatlist_container), event_box, FALSE, FALSE, 0);
    // gtk_widget_set_name(event_box, mx_itoa(id));
    gtk_widget_set_name(event_box, chat_name);
    add_class(event_box, "chatlist_item_wrap");
	g_signal_connect(G_OBJECT(event_box), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
	g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(chatlist_item_on_click), NULL);

    GtkWidget *chatlist_item = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(chatlist_item, mx_itoa(id));
    add_class(chatlist_item, "chatlist_item");
    gtk_container_add(GTK_CONTAINER(event_box), chatlist_item);

    GtkWidget *chatlist_item_id = gtk_label_new(mx_itoa(id)); ///CHAT ID
    gtk_widget_set_name(chatlist_item_id, "chat_id");
    add_class(chatlist_item_id, "hidden");
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_id, FALSE, FALSE, 0);

    // GtkWidget *avatar = gtk_drawing_area_new();
    GtkWidget *avatar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 34, 34);
    // g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar), (gpointer)(intptr_t)list->avatar);   // Получить avatar пользовтеля
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    add_class(avatar, "chatlist_item_avatar");
    gtk_box_pack_start(GTK_BOX(chatlist_item), avatar, FALSE, FALSE, 0);

    // text block
    GtkWidget *chatlist_item_text = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_text, false, false, 0);
    add_class(chatlist_item_text, "chatlist_item_text");

    GtkWidget *chatlist_item_title = gtk_label_new(chat_name);
    // gtk_widget_set_name(chatlist_item_title, "chat_name");
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item_text), chatlist_item_title, false, false, 0);
    
    GtkWidget *chatlist_item_message = NULL;
    GtkWidget *chatlist_item_time = NULL;
    GtkWidget *chatlist_item_notify = NULL;

    t_chat* curr_chat = mx_get_chat_by_name(utils->chatlist, chat_name);
    if (curr_chat && curr_chat->last_new_msg)
    {
        chatlist_item_message = gtk_label_new(curr_chat->last_new_msg->text);
        chatlist_item_time = gtk_label_new(curr_chat->last_new_msg->date_str);
        chatlist_item_notify = gtk_label_new(mx_itoa(curr_chat->new_msg_count));
    }
    else if (!curr_chat->last_new_msg)
    {
        chatlist_item_message = gtk_label_new("No messages yet");
        chatlist_item_time = gtk_label_new("");
        chatlist_item_notify = gtk_label_new("0");
    }

    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_message), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item_text), chatlist_item_message, false, false, 0);
    gtk_widget_set_name(chatlist_item_message, "chatlist_item_message");
    //

    // info block
    GtkWidget *chatlist_item_info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_info), GTK_ALIGN_END);
    // gtk_widget_set_valign(GTK_WIDGET(chatlist_item_info), GTK_ALIGN_END);
    gtk_box_pack_end(GTK_BOX(chatlist_item), chatlist_item_info, false, false, 0);
    add_class(chatlist_item_info, "chatlist_item_info");

    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_time), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_time), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(chatlist_item_info), chatlist_item_time, false, false, 0);
    gtk_widget_set_name(chatlist_item_time, "chatlist_item_time");
    add_class(chatlist_item_time, "chatlist_item_time");

    gtk_widget_set_size_request(GTK_WIDGET(chatlist_item_notify), 20, 20);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_notify), GTK_ALIGN_END);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_notify), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(chatlist_item_info), chatlist_item_notify, false, false, 0);
    gtk_widget_set_name(chatlist_item_notify, "chatlist_item_notify");
    add_class(chatlist_item_notify, "chatlist_item_notify");
    //

    gtk_widget_show_all(event_box);
}

void build_chatlist_message(char *message)
{
    GtkWidget *chatlist = get_widget_by_name_r(main_window, "chatlist");
    clear_container(chatlist);

    GtkWidget *chatlist_notify_label = gtk_label_new(message);
    gtk_widget_set_name(chatlist_notify_label, "chatlist_notify_label");
    add_class(chatlist_notify_label, "chatscreen_notify");
    gtk_widget_set_halign(GTK_WIDGET(chatlist_notify_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_notify_label), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chatlist), chatlist_notify_label, FALSE, FALSE, 0);
    gtk_widget_set_vexpand(chatlist_notify_label, TRUE);
    gtk_widget_set_hexpand(chatlist_notify_label, TRUE);

    gtk_widget_show_all(chatlist);
}
