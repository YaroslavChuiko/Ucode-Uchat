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

}

void build_confirm_leave_chat_window(GtkWidget *widget, gpointer data) {
    if (widget){};

    GtkWidget *popup_window = create_popup_window(200, 150);
    GtkWidget *confirm_leave_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    gtk_widget_set_size_request(GTK_WIDGET(confirm_leave_chat_box), 200, 150);
	gtk_container_add(GTK_CONTAINER(popup_window), confirm_leave_chat_box);
    add_class(confirm_leave_chat_box, "edit_profile_menu");

    GtkWidget *confirm_leave_chat_title = gtk_label_new("Leave chat");
    gtk_widget_set_halign(GTK_WIDGET(confirm_leave_chat_title), GTK_ALIGN_CENTER);

    GtkWidget *confirm_leave_chat_label = gtk_label_new("Are you sure you want to leave chat?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_leave_chat_label), GTK_ALIGN_CENTER);

    GtkWidget *confirm_leave_chat_btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
    gtk_widget_set_halign(GTK_WIDGET(confirm_leave_chat_btn_box), GTK_ALIGN_CENTER);

    GtkWidget *confirm_leave_chat_btn = gtk_button_new_with_label("Leave");
    g_signal_connect(G_OBJECT(confirm_leave_chat_btn), "clicked", G_CALLBACK(leave_chat_btn_click), NULL);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_btn_box), confirm_leave_chat_btn, FALSE, FALSE, 0);

    GtkWidget *cancel_leave_chat_btn = gtk_button_new_with_label("Cancel");
    g_signal_connect(G_OBJECT(cancel_leave_chat_btn), "clicked", G_CALLBACK(cancel_btn_click), NULL);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_btn_box), cancel_leave_chat_btn, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), confirm_leave_chat_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), confirm_leave_chat_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), confirm_leave_chat_btn_box, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

