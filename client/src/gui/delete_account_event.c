#include "../../inc/client.h"

void delete_account_btn_click(GtkWidget *widget, gpointer data) {
    if (widget){};

    if (handle_delete_account_request() == R_SUCCESS) {
        client_cleanup(false);
        build_authorizatioin_window();
    }

}

void build_confirm_delete_account_window(GtkWidget *widget, gpointer data) {
    if (widget){};

    GtkWidget *popup_window = create_popup_window(200, 150);
    GtkWidget *confirm_delete_account_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    gtk_widget_set_size_request(GTK_WIDGET(confirm_delete_account_box), 200, 150);
	gtk_container_add(GTK_CONTAINER(popup_window), confirm_delete_account_box);
    add_class(confirm_delete_account_box, "edit_profile_menu");

    GtkWidget *confirm_delete_account_title = gtk_label_new("Delete account");
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_account_title), GTK_ALIGN_CENTER);

    GtkWidget *confirm_delete_account_label = gtk_label_new("Are you sure you want to delete account?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_account_label), GTK_ALIGN_CENTER);

    GtkWidget *confirm_delete_account_btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_account_btn_box), GTK_ALIGN_CENTER);

    GtkWidget *confirm_delete_account_btn = gtk_button_new_with_label("Delete");
    g_signal_connect(G_OBJECT(confirm_delete_account_btn), "clicked", G_CALLBACK(delete_account_btn_click), NULL);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_btn_box), confirm_delete_account_btn, FALSE, FALSE, 0);

    GtkWidget *cancel_delete_account_btn = gtk_button_new_with_label("Cancel");
    g_signal_connect(G_OBJECT(cancel_delete_account_btn), "clicked", G_CALLBACK(cancel_btn_click), NULL);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_btn_box), cancel_delete_account_btn, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), confirm_delete_account_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), confirm_delete_account_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), confirm_delete_account_btn_box, FALSE, FALSE, 0);

    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}

