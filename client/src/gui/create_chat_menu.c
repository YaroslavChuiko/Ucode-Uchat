#include "../../inc/client.h"

void build_create_chat_menu(GtkWidget *main_area)
{
    GtkWidget*  popup_window = create_popup_window(400, 300);
    // t_chat_screen.popup_menu = popup_window; //????

    GtkWidget *create_chat_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_widget_set_name(GTK_WIDGET(create_chat_menu), "Create new group");
    gtk_widget_set_size_request(GTK_WIDGET(create_chat_menu), 400, 300);
	gtk_container_add(GTK_CONTAINER(popup_window), create_chat_menu );
    // gtk_container_add(GTK_CONTAINER(create_chat_wrap), create_chat_menu);
    add_class(create_chat_menu, "create_chat_menu");

    GtkWidget *menu_title = gtk_label_new("Create new chat");
    gtk_widget_set_halign(GTK_WIDGET(menu_title), GTK_ALIGN_CENTER);

    GtkWidget *chat_name_label = gtk_label_new("Chat name:");
    gtk_widget_set_halign(GTK_WIDGET(chat_name_label), GTK_ALIGN_START);
    GtkWidget *chat_name_field = gtk_entry_new();
    gtk_widget_set_name(chat_name_field, "chat_name_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat_name_field), "Chat name");

    GtkWidget *chat_name_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(chat_name_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(chat_name_notify_label, "chat_name_notify_label");
    add_class(chat_name_notify_label, "notify-label");

    GtkWidget *create_chat_btn = gtk_button_new_with_label("Create chat");
    g_signal_connect(G_OBJECT(create_chat_btn), "clicked", G_CALLBACK(create_chat_btn_click), NULL);

    gtk_box_pack_start(GTK_BOX(create_chat_menu), menu_title, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), create_chat_btn, FALSE, FALSE, 30);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus (popup_window);
}
