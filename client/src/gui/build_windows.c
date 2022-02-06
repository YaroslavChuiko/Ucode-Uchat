#include "../../inc/client.h"

static void destroy(GtkWidget* widget, gpointer data)
{
    if(widget){}
    (void)data;

    pthread_cancel(utils->th_reader);
	handle_logout_request(true);
	client_cleanup(true);
    gtk_main_quit();
}

GtkWidget* create_new_window(char *title, int width, int height, bool resizable)
{
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), resizable);
    g_signal_connect(window, "delete_event", G_CALLBACK(destroy), NULL);

	return window;
}

void build_authorization_window()
{
	if (main_window)
        gtk_widget_destroy(main_window);

	main_window = create_new_window("Authorization", 500, 0, false);

	GtkWidget* main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(main_area, "main_area");
	gtk_container_add(GTK_CONTAINER(main_window), main_area);

	build_login_menu();
	gtk_widget_show_all(main_window);
}

void build_chat_window()
{
    if (main_window)
        gtk_widget_destroy(main_window);

    main_window = create_new_window("UChat", 500, 0, true);

    GtkWidget* main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(main_area, "main_area");
    gtk_container_add(GTK_CONTAINER(main_window), main_area);

    build_chat_screen();
    gtk_widget_show_all(main_window);
}

void destroy_popup_window(GtkWidget *widget, gpointer chat_screen)
{
    if(widget){}
    (void)chat_screen;

    GtkWidget *popup_window = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(popup_window);
}

GtkWidget *create_popup_window(int width, int height)
{
    GtkWidget*  popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //GTK_WINDOW_POPUP
    // t_chat_screen.popup_menu = popup_window;
    gtk_widget_set_name(GTK_WIDGET(popup_window), "popup_window");
    gtk_window_set_default_size(GTK_WINDOW(popup_window), width, height);
    gtk_window_set_transient_for(GTK_WINDOW(popup_window), GTK_WINDOW(main_window));
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popup_window), TRUE);
	gtk_window_set_position(GTK_WINDOW(popup_window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_decorated(GTK_WINDOW(popup_window), FALSE);
    add_class(popup_window, "popup_window");
    g_signal_connect(G_OBJECT(popup_window), "focus-out-event", G_CALLBACK(destroy_popup_window), NULL);

    return popup_window;
}
