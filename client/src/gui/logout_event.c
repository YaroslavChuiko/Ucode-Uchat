#include "../../inc/client.h"

void logout_btn_click(GtkWidget *widget, gpointer data)
{
    if (widget){};
    
    handle_logout_request(false);
	client_cleanup(false);
    build_authorizatioin_window();
}

void cancel_btn_click(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(toplevel);
}

void build_confirm_logout_window(GtkWidget *widget, gpointer data) {
    if (widget){};

    GtkWidget *popup_window = create_popup_window(200, 150);
    GtkWidget *confirm_logout_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    gtk_widget_set_size_request(GTK_WIDGET(confirm_logout_box), 200, 150);
	gtk_container_add(GTK_CONTAINER(popup_window), confirm_logout_box);
    add_class(confirm_logout_box, "edit_profile_menu");

    GtkWidget *confirm_logout_title = gtk_label_new("Log out");
    gtk_widget_set_halign(GTK_WIDGET(confirm_logout_title), GTK_ALIGN_CENTER);

    GtkWidget *confirm_logout_label = gtk_label_new("Are you sure you want to log out?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_logout_label), GTK_ALIGN_CENTER);

    GtkWidget *confirm_logout_btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
    gtk_widget_set_halign(GTK_WIDGET(confirm_logout_btn_box), GTK_ALIGN_CENTER);

    GtkWidget *confirm_logout_btn = gtk_button_new_with_label("Log out");
    g_signal_connect(G_OBJECT(confirm_logout_btn), "clicked", G_CALLBACK(logout_btn_click), NULL);
    gtk_box_pack_start(GTK_BOX(confirm_logout_btn_box), confirm_logout_btn, FALSE, FALSE, 0);

    GtkWidget *cancel_logout_btn = gtk_button_new_with_label("Cancel");
    g_signal_connect(G_OBJECT(cancel_logout_btn), "clicked", G_CALLBACK(cancel_btn_click), NULL);
    gtk_box_pack_start(GTK_BOX(confirm_logout_btn_box), cancel_logout_btn, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(confirm_logout_box), confirm_logout_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_logout_box), confirm_logout_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_logout_box), confirm_logout_btn_box, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

