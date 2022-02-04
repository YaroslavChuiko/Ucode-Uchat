#include "../../inc/client.h"

void leave_chat_btn_click(GtkWidget *widget, gpointer data) {

    int response_code = handle_leave_chat_request(utils->current_chat->name);

    if (response_code == R_SUCCESS)
    {
        utils->current_chat = NULL;
        update_chatlist();
        // build_start_messaging_label();

        GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
        gtk_widget_destroy(toplevel);
    }
    (void)data;
}

void build_confirm_leave_chat_window(GtkWidget *widget, gpointer data) {
    if(widget){}
    (void)data;

    GtkWidget *popup_window = create_popup_window(400, 0);
    GtkWidget *confirm_leave_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // gtk_widget_set_size_request(GTK_WIDGET(confirm_leave_chat_box), 200, 150);
	gtk_container_add(GTK_CONTAINER(popup_window), confirm_leave_chat_box);
    add_class(confirm_leave_chat_box, "popup_menu");
    add_class(confirm_leave_chat_box, "edit_profile_menu");

    GtkWidget *confirm_leave_chat_title = gtk_label_new("Leave chat");
    gtk_widget_set_halign(GTK_WIDGET(confirm_leave_chat_title), GTK_ALIGN_CENTER);
    add_class(confirm_leave_chat_title, "popup_window_title");

    GtkWidget *confirm_leave_chat_label = gtk_label_new("Are you sure you want to leave chat?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_leave_chat_label), GTK_ALIGN_CENTER);
    add_class(confirm_leave_chat_label, "confirm_text");

    //btn box
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    GtkWidget *confirm_leave_chat_btn = gtk_button_new_with_label("Leave");
    gtk_widget_set_size_request(GTK_WIDGET(confirm_leave_chat_btn), 150, 50);
    g_signal_connect(G_OBJECT(confirm_leave_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_leave_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_leave_chat_btn), "clicked", G_CALLBACK(leave_chat_btn_click), NULL);
    add_class(confirm_leave_chat_btn, "btn");
	add_class(confirm_leave_chat_btn, "btn--blue");

    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
	add_class(cancel_btn, "btn--dark-blue");

    gtk_box_pack_end(GTK_BOX(btn_box), confirm_leave_chat_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);
    //

    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), confirm_leave_chat_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), confirm_leave_chat_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), btn_box, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

