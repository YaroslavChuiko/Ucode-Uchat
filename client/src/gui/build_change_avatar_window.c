#include "../../inc/client.h"

void change_avatar_btn_click(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    (void)data;

    GtkWidget *path_field = get_widget_by_name_r(toplevel, "path_field");
    GtkWidget *path_notify_label = get_widget_by_name_r(toplevel, "path_notify_label");

    char *new_avatar = (char*)gtk_entry_get_text(GTK_ENTRY(path_field));

    // handle_update_user_image(new_avatar);
    // usleep(4000000);
    // handle_get_user_image(utils->current_user->user_id, &utils->current_user->avatar_path);

    gtk_widget_destroy(toplevel);
}

void build_change_avatar_window(GtkWidget *widget, gpointer data) {
    if (widget){};
    (void)data;

    GtkWidget *popup_window = create_popup_window(450, 0);
    GtkWidget *change_login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_container_add(GTK_CONTAINER(popup_window), change_login_box);
    add_class(change_login_box, "popup_menu");

    GtkWidget *change_avatar_title = gtk_label_new("Change avatar");
    gtk_widget_set_halign(GTK_WIDGET(change_avatar_title), GTK_ALIGN_CENTER);
    add_class(change_avatar_title, "popup_window_title");

    GtkWidget *path_label = gtk_label_new("New avatar path:");
    gtk_widget_set_halign(GTK_WIDGET(path_label), GTK_ALIGN_START);
    add_class(path_label, "input-field_title");
    GtkWidget *path_field = gtk_entry_new();
    gtk_widget_set_name(path_field, "path_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(path_field), "Avatar path");
    add_class(path_field, "input-field");
    add_class(path_field, "input-field--name");

    GtkWidget *path_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(path_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(path_notify_label, "path_notify_label");
    add_class(path_notify_label, "notify-label");

    //btn box
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    GtkWidget *change_login_btn = gtk_button_new_with_label("Submit");
    gtk_widget_set_size_request(GTK_WIDGET(change_login_btn), 150, 50);
    g_signal_connect(G_OBJECT(change_login_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_login_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_login_btn), "clicked", G_CALLBACK(change_avatar_btn_click), NULL);
    add_class(change_login_btn, "btn");
	add_class(change_login_btn, "btn--blue");

    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
	add_class(cancel_btn, "btn--dark-blue");

    gtk_box_pack_end(GTK_BOX(btn_box), change_login_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);
    //

    gtk_box_pack_start(GTK_BOX(change_login_box), change_avatar_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), path_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), path_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), path_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), btn_box, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
