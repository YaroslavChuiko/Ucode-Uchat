#include "../../inc/client.h"

void focus_out_current_password_field(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *current_password_field = get_widget_by_name_r(toplevel, "current_password_field");
    GtkWidget *current_password_notify_label = get_widget_by_name_r(toplevel, "current_password_notify_label");
    if (validate_password_field(current_password_field, current_password_notify_label)) {
        char *current_password = (char*)gtk_entry_get_text(GTK_ENTRY(current_password_field));
        if (mx_strcmp(current_password, utils->current_user->password) != 0) {
            set_field_error_style(current_password_field);
            set_notify_error_style(current_password_notify_label, "Incorrect password");
        }
        else {
            set_field_success_style(current_password_field);
            set_notify_success_style(current_password_notify_label, "");
        }
    }
}

void focus_out_new_password_field(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *new_password_field = get_widget_by_name_r(toplevel, "new_password_field");
    GtkWidget *new_password_notify_label = get_widget_by_name_r(toplevel, "new_password_notify_label");
    validate_password_field(new_password_field, new_password_notify_label);
}

void focus_out_re_new_password_field(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *new_password_field = get_widget_by_name_r(toplevel, "new_password_field");
    GtkWidget *re_new_password_field = get_widget_by_name_r(toplevel, "re_new_password_field");
    GtkWidget *re_new_password_notify_label = get_widget_by_name_r(toplevel, "re_new_password_notify_label");
    validate_repassword_field(new_password_field, re_new_password_field, re_new_password_notify_label);
}

void change_password_btn_click(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    GtkWidget *current_password_field = get_widget_by_name_r(toplevel, "current_password_field");
    GtkWidget *current_password_notify_label = get_widget_by_name_r(toplevel, "current_password_notify_label");
    GtkWidget *new_password_field = get_widget_by_name_r(toplevel, "new_password_field");
    GtkWidget *new_password_notify_label = get_widget_by_name_r(toplevel, "new_password_notify_label");
    GtkWidget *re_new_password_field = get_widget_by_name_r(toplevel, "re_new_password_field");
    GtkWidget *re_new_password_notify_label = get_widget_by_name_r(toplevel, "re_new_password_notify_label");
    GtkWidget *change_password_notify_label = get_widget_by_name_r(toplevel, "change_password_notify_label");

    bool current_password_field_valid = validate_password_field(current_password_field, current_password_notify_label);

    char *current_password = (char*)gtk_entry_get_text(GTK_ENTRY(current_password_field));

    if (current_password_field_valid) {
        if (mx_strcmp(current_password, utils->current_user->password) != 0) {
            set_field_error_style(current_password_field);
            set_notify_error_style(current_password_notify_label, "Incorrect password");
        }
        else {
            set_field_success_style(current_password_field);
            set_notify_success_style(current_password_notify_label, "");
        }
    }

    bool new_password_field_valid = validate_password_field(new_password_field, new_password_notify_label);
    bool re_new_password_field_valid = validate_repassword_field(new_password_field, re_new_password_field, re_new_password_notify_label);

	if (!current_password_field_valid || !new_password_field_valid || !re_new_password_field_valid) {
        set_notify_error_style(change_password_notify_label, "Please fill all fields correctly!");
        return;
	}
    else {
        set_notify_success_style(change_password_notify_label, "");
    }

	char *new_password = (char*)gtk_entry_get_text(GTK_ENTRY(new_password_field));

    int response_code = handle_edit_password_request(new_password, current_password);
    handle_edit_password_response_code(response_code, change_password_notify_label);
}

void build_change_password_window(GtkWidget *widget, gpointer data) {
    if (widget){};

    GtkWidget *popup_window = create_popup_window(400, 300);
    GtkWidget *change_password_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_widget_set_size_request(GTK_WIDGET(change_password_box), 400, 300);
	gtk_container_add(GTK_CONTAINER(popup_window), change_password_box);
    add_class(change_password_box, "edit_profile_menu");

    GtkWidget *change_password_title = gtk_label_new("Change password");
    gtk_widget_set_halign(GTK_WIDGET(change_password_title), GTK_ALIGN_CENTER);

    GtkWidget *current_password_label = gtk_label_new("Current password:");
    gtk_widget_set_halign(GTK_WIDGET(current_password_label), GTK_ALIGN_START);
    GtkWidget *current_password_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(current_password_field), false);
    gtk_widget_set_name(current_password_field, "current_password_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(current_password_field), "Current password");
    g_signal_connect(G_OBJECT(current_password_field), "focus-out-event", G_CALLBACK(focus_out_current_password_field), NULL);

    GtkWidget *current_password_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(current_password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(current_password_notify_label, "current_password_notify_label");
    add_class(current_password_notify_label, "notify-label");

    GtkWidget *new_password_label = gtk_label_new("New password:");
    gtk_widget_set_halign(GTK_WIDGET(new_password_label), GTK_ALIGN_START);
    GtkWidget *new_password_field = gtk_entry_new();
    g_signal_connect(G_OBJECT(new_password_field), "focus-out-event", G_CALLBACK(focus_out_new_password_field), NULL);
    gtk_entry_set_visibility(GTK_ENTRY(new_password_field), false);
    gtk_widget_set_name(new_password_field, "new_password_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_password_field), "New password");

    GtkWidget *new_password_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(new_password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(new_password_notify_label, "new_password_notify_label");
    add_class(new_password_notify_label, "notify-label");

    GtkWidget *re_new_password_label = gtk_label_new("Repeat password:");
    gtk_widget_set_halign(GTK_WIDGET(re_new_password_label), GTK_ALIGN_START);
    GtkWidget *re_new_password_field = gtk_entry_new();
    g_signal_connect(G_OBJECT(re_new_password_field), "focus-out-event", G_CALLBACK(focus_out_re_new_password_field), NULL);
    gtk_entry_set_visibility(GTK_ENTRY(re_new_password_field), false);
    gtk_widget_set_name(re_new_password_field, "re_new_password_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(re_new_password_field), "Password");

    GtkWidget *re_new_password_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(re_new_password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(re_new_password_notify_label, "re_new_password_notify_label");
    add_class(re_new_password_notify_label, "notify-label");

    GtkWidget *change_password_btn = gtk_button_new_with_label("Change password");
    g_signal_connect(G_OBJECT(change_password_btn), "clicked", G_CALLBACK(change_password_btn_click), NULL);

    GtkWidget *change_password_notify_label = gtk_label_new(" ");
	gtk_widget_set_halign(change_password_notify_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(change_password_notify_label, "change_password_notify_label");
	add_class(change_password_notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(change_password_box), change_password_title, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(change_password_box), current_password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), current_password_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), current_password_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), new_password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), new_password_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), new_password_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), re_new_password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), re_new_password_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), re_new_password_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), change_password_btn, FALSE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(change_password_box), change_password_notify_label, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

