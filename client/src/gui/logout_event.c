#include "../../inc/client.h"

void logout_btn_click(GtkWidget *widget, gpointer data)
{
    if(widget){}
    (void)data;
    
    pthread_cancel(utils->th_reader);
    handle_logout_request(false);
	client_cleanup(false);
    pthread_create(&utils->th_reader, NULL, handle_server_updates, NULL);
    build_authorization_window();
}

void build_confirm_logout_window(GtkWidget *widget, gpointer data) {
    if(widget){}
    (void)data;

    GtkWidget *popup_window = create_popup_window(400, 0);
    GtkWidget *confirm_logout_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_container_add(GTK_CONTAINER(popup_window), confirm_logout_box);
    add_class(confirm_logout_box, "popup_menu");
    add_class(confirm_logout_box, "edit_profile_menu");

    GtkWidget *confirm_logout_title = gtk_label_new("Log out");
    gtk_widget_set_halign(GTK_WIDGET(confirm_logout_title), GTK_ALIGN_CENTER);
    add_class(confirm_logout_title, "popup_window_title");

    GtkWidget *confirm_logout_label = gtk_label_new("Are you sure you want to log out?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_logout_label), GTK_ALIGN_CENTER);
    add_class(confirm_logout_label, "confirm_text");

    //btn box
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    GtkWidget *confirm_logout_btn = gtk_button_new_with_label("Log out");
    gtk_widget_set_size_request(GTK_WIDGET(confirm_logout_btn), 150, 50);
    g_signal_connect(G_OBJECT(confirm_logout_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_logout_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_logout_btn), "clicked", G_CALLBACK(logout_btn_click), NULL);
    add_class(confirm_logout_btn, "btn");
	add_class(confirm_logout_btn, "btn--blue");

    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
	add_class(cancel_btn, "btn--dark-blue");

    gtk_box_pack_end(GTK_BOX(btn_box), confirm_logout_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);
    //

    gtk_box_pack_start(GTK_BOX(confirm_logout_box), confirm_logout_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_logout_box), confirm_logout_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_logout_box), btn_box, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

