#include "../../inc/client.h"

void build_start_messaging_label()
{
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");

    clear_container(chat_container);

    GtkWidget *messaging_label = gtk_label_new("Select a chat to start messaging");
    gtk_widget_set_halign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_vexpand(messaging_label, TRUE);
    gtk_widget_set_hexpand(messaging_label, TRUE);
    add_class(messaging_label, "chatscreen_notify");

    gtk_box_pack_start(GTK_BOX(chat_container), messaging_label, FALSE, FALSE, 0);

    gtk_widget_show_all(chat_container);
}

void build_rightbar(GtkWidget *chat_screen)
{
    GtkWidget *chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(chat, TRUE);
    gtk_widget_set_vexpand(chat, TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(chat), WINDOW_WIDTH - LEFT_BAR_W, WINDOW_HEIGHT);
    gtk_grid_attach(GTK_GRID(chat_screen), chat, 1, 0, 2, 1);
    gtk_widget_set_name(chat, "chat");
    add_class(chat, "chat");

    // build_start_messaging_label();
}

void build_chat_screen()
{
	GtkWidget* main_area = get_widget_by_name_r(main_window, "main_area");
    GtkWidget *grid = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);
    gtk_container_add(GTK_CONTAINER(main_area), grid);

    build_leftbar(grid);
    build_rightbar(grid);

    update_chatlist();

    gtk_widget_show_all(grid);
}
