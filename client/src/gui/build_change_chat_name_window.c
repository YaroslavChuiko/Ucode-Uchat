#include "../../inc/client.h"

void focus_out_chat_name_field(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    GtkWidget *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");
    validate_name_field(chat_name_field, chat_name_notify_label);
}

void change_chat_name_btn_click(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    GtkWidget *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");
    GtkWidget *change_chat_name_notify_label = get_widget_by_name_r(toplevel, "change_chat_name_notify_label");

    if (!validate_name_field(chat_name_field, chat_name_notify_label)) {
        set_notify_error_style(change_chat_name_notify_label, "Please fill all fields correctly!");
        return;
    }
    else {
        set_notify_success_style(change_chat_name_notify_label, "");
    }

    char *new_chat_name = (char*)gtk_entry_get_text(GTK_ENTRY(chat_name_field));

    int response_code = handle_edit_chat_request(utils->current_chat->id, new_chat_name);
    if (response_code != R_SUCCESS) {
        set_field_error_style(chat_name_field);
    }
    handle_edit_chat_response_code(response_code, change_chat_name_notify_label);
}

void build_change_chat_name_window(GtkWidget *widget, gpointer data) {
    if (widget){};

    GtkWidget *popup_window = create_popup_window(400, 300);
    GtkWidget *change_chat_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_widget_set_size_request(GTK_WIDGET(change_chat_name_box), 400, 300);
	gtk_container_add(GTK_CONTAINER(popup_window), change_chat_name_box);
    add_class(change_chat_name_box, "edit_profile_menu");

    GtkWidget *change_chat_name_title = gtk_label_new("Change chat menu");
    gtk_widget_set_halign(GTK_WIDGET(change_chat_name_title), GTK_ALIGN_CENTER);

    GtkWidget *chat_name_label = gtk_label_new("New chat name:");
    gtk_widget_set_halign(GTK_WIDGET(chat_name_label), GTK_ALIGN_START);
    GtkWidget *chat_name_field = gtk_entry_new();
    gtk_widget_set_name(chat_name_field, "chat_name_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat_name_field), "Chat name");
    g_signal_connect(G_OBJECT(chat_name_field), "focus-out-event", G_CALLBACK(focus_out_chat_name_field), NULL);

    GtkWidget *chat_name_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(chat_name_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(chat_name_notify_label, "chat_name_notify_label");
    add_class(chat_name_notify_label, "notify-label");

    GtkWidget *change_chat_name_btn = gtk_button_new_with_label("Change chat name");
    g_signal_connect(G_OBJECT(change_chat_name_btn), "clicked", G_CALLBACK(change_chat_name_btn_click), NULL);

    GtkWidget *change_chat_name_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(change_chat_name_notify_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(change_chat_name_notify_label, "change_chat_name_notify_label");
	add_class(change_chat_name_notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(change_chat_name_box), change_chat_name_title, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(change_chat_name_box), chat_name_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_chat_name_box), chat_name_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_chat_name_box), chat_name_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_chat_name_box), change_chat_name_btn, FALSE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(change_chat_name_box), change_chat_name_notify_label, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

