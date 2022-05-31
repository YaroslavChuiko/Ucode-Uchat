#include "../../inc/client.h"

void build_create_chat_menu()
{
    GtkWidget*  popup_window = create_popup_window(450, 0);

    GtkWidget *create_chat_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(popup_window), create_chat_menu );
    add_class(create_chat_menu, "popup_menu");

    GtkWidget *menu_title = gtk_label_new("Create new chat");
    gtk_widget_set_halign(GTK_WIDGET(menu_title), GTK_ALIGN_CENTER);
    add_class(menu_title, "popup_window_title");

    GtkWidget *chat_name_label = gtk_label_new("Chat name:");
    gtk_widget_set_halign(GTK_WIDGET(chat_name_label), GTK_ALIGN_START);
    add_class(chat_name_label, "input-field_title");
    GtkWidget *chat_name_field = gtk_entry_new();
    gtk_widget_set_name(chat_name_field, "chat_name_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat_name_field), "Chat name");
    add_class(chat_name_field, "input-field");
    add_class(chat_name_field, "input-field--name");

    GtkWidget *chat_name_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(chat_name_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(chat_name_notify_label, "chat_name_notify_label");
    add_class(chat_name_notify_label, "notify-label");

    //btn box
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    GtkWidget *create_chat_btn = gtk_button_new_with_label("Create");
    gtk_widget_set_size_request(GTK_WIDGET(create_chat_btn), 150, 50);
    g_signal_connect(G_OBJECT(create_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_chat_btn), "clicked", G_CALLBACK(create_chat_btn_click), NULL);
    add_class(create_chat_btn, "btn");
	add_class(create_chat_btn, "btn--blue");

    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
	add_class(cancel_btn, "btn--dark-blue");

    gtk_box_pack_end(GTK_BOX(btn_box), create_chat_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);
    //

    gtk_box_pack_start(GTK_BOX(create_chat_menu), menu_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), btn_box, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus (popup_window);
}
