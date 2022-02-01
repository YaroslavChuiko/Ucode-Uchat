#include "../../inc/client.h"

void focus_out_login_field(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *login_field = get_widget_by_name_r(toplevel, "login_field");
    GtkWidget *login_notify_label = get_widget_by_name_r(toplevel, "login_notify_label");
    validate_name_field(login_field, login_notify_label);
}

void change_login_btn_click(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *login_field = get_widget_by_name_r(toplevel, "login_field");
    GtkWidget *login_notify_label = get_widget_by_name_r(toplevel, "login_notify_label");
    GtkWidget *change_login_notify_label = get_widget_by_name_r(toplevel, "change_login_notify_label");

    if (!validate_name_field(login_field, login_notify_label)) {
        set_notify_error_style(change_login_notify_label, "Please fill all fields correctly!");
        return;
    }
    else {
        set_notify_success_style(change_login_notify_label, "");
    }

    char *new_login = (char*)gtk_entry_get_text(GTK_ENTRY(login_field));

    int response_code = handle_edit_username_request(new_login);
    if (response_code != R_SUCCESS) {
        set_field_error_style(login_field);
    }
    handle_edit_username_response_code(response_code, change_login_notify_label);
}

void build_change_login_window(GtkWidget *widget, gpointer data) {
    if (widget){};

    GtkWidget *popup_window = create_popup_window(400, 300);
    GtkWidget *change_login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_widget_set_size_request(GTK_WIDGET(change_login_box), 400, 300);
	gtk_container_add(GTK_CONTAINER(popup_window), change_login_box);
    add_class(change_login_box, "edit_profile_menu");

    GtkWidget *change_login_title = gtk_label_new("Change login");
    gtk_widget_set_halign(GTK_WIDGET(change_login_title), GTK_ALIGN_CENTER);

    GtkWidget *login_label = gtk_label_new("New login:");
    gtk_widget_set_halign(GTK_WIDGET(login_label), GTK_ALIGN_START);
    GtkWidget *login_field = gtk_entry_new();
    gtk_widget_set_name(login_field, "login_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_field), "Login");
    g_signal_connect(G_OBJECT(login_field), "focus-out-event", G_CALLBACK(focus_out_login_field), NULL);

    GtkWidget *login_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(login_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(login_notify_label, "login_notify_label");
    add_class(login_notify_label, "notify-label");

    GtkWidget *change_login_btn = gtk_button_new_with_label("Change login");
    g_signal_connect(G_OBJECT(change_login_btn), "clicked", G_CALLBACK(change_login_btn_click), NULL);

    GtkWidget *change_login_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(change_login_notify_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(change_login_notify_label, "change_login_notify_label");
	add_class(change_login_notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(change_login_box), change_login_title, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(change_login_box), login_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), login_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), login_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), change_login_btn, FALSE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(change_login_box), change_login_notify_label, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

