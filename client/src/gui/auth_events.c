#include "../../inc/client.h"

void switch_to_login_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    // if(widget){}
    // if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
        GtkWidget *signup_menu = get_widget_by_name_r(toplevel, "signup_menu");
        gtk_widget_destroy(GTK_WIDGET(signup_menu));
        build_login_menu((GtkWidget**)main_area);
    // }
}

void switch_to_signup_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    // if(widget){}
    // if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
        GtkWidget *login_menu = get_widget_by_name_r(toplevel, "login_menu");
        gtk_widget_destroy(GTK_WIDGET(login_menu));
        build_signup_menu((GtkWidget**)main_area);
    // }
}

void focus_out_username_field(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *username_field = get_widget_by_name_r(toplevel, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(toplevel, "username_notify_label");
    validate_name_field(username_field, username_notify_label);
}

void focus_out_password_field(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *password_field = get_widget_by_name_r(toplevel, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(toplevel, "password_notify_label");
    validate_password_field(password_field, password_notify_label);
}

void focus_out_repassword_field(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *password_field = get_widget_by_name_r(toplevel, "password_field");
    GtkWidget *repassword_field = get_widget_by_name_r(toplevel, "repassword_field");
    GtkWidget *repassword_notify_label = get_widget_by_name_r(toplevel, "repassword_notify_label");
    validate_repassword_field(password_field, repassword_field, repassword_notify_label);
}

void signup_button_click(GtkWidget *widget, gpointer main_area)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *username_field = get_widget_by_name_r(toplevel, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(toplevel, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(toplevel, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(toplevel, "password_notify_label");
    GtkWidget *repassword_field = get_widget_by_name_r(toplevel, "repassword_field");
    GtkWidget *repassword_notify_label = get_widget_by_name_r(toplevel, "repassword_notify_label");
    GtkWidget *signup_notify_label = get_widget_by_name_r(toplevel, "signup_notify_label");

    bool username_field_valid = validate_name_field(username_field, username_notify_label);
    bool password_field_valid = validate_password_field(password_field, password_notify_label);
    bool repassword_field_valid = validate_repassword_field(password_field, repassword_field, repassword_notify_label);

	if (!username_field_valid || !password_field_valid || !repassword_field_valid)
	{
        set_notify_error_style(signup_notify_label, "Please fill all fields correctly!");
        return;
	}
    else 
    {
        set_notify_success_style(signup_notify_label, "");
    }

    char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field)));
	char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));

	int error_code = handle_signup_request(user_name, user_password);
    handle_signup_error_code(error_code, signup_notify_label);

    if(error_code == R_SUCCESS)
    {
        GtkWidget *signup_menu = get_widget_by_name_r(toplevel, "signup_menu");
        gtk_widget_destroy(signup_menu);
        build_login_menu((GtkWidget**)main_area);
    }
}

void login_button_click(GtkWidget *widget, gpointer main_area)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *username_field = get_widget_by_name_r(toplevel, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(toplevel, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(toplevel, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(toplevel, "password_notify_label");
    GtkWidget *login_notify_label = get_widget_by_name_r(toplevel, "login_notify_label");

    bool username_field_is_empty = is_empty_field(username_field, username_notify_label);
    bool password_field_is_empty = is_empty_field(password_field, password_notify_label);

    if (username_field_is_empty || password_field_is_empty)
	{
        return;
	}

	char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field)));
	char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));

    int error_code = handle_login_request(user_name, user_password);
    handle_login_error_code(error_code, login_notify_label);

	if(error_code == R_SUCCESS)
    {
        gtk_widget_destroy(main_window);
	    main_window = create_new_window("UChat", 500, 0, true);

        GtkWidget* main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	    gtk_container_add(GTK_CONTAINER(main_window), main_area);

        build_chat_screen(&main_area);
        gtk_widget_show_all(main_window);
    }
}
