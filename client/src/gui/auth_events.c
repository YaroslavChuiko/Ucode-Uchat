#include "../../inc/client.h"

void switch_to_login_menu(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if(widget){}
    // if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkWidget *signup_menu = get_widget_by_name_r(main_window, "signup_menu");
        gtk_widget_destroy(GTK_WIDGET(signup_menu));
        build_login_menu();
    // }
}

void switch_to_signup_menu(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if(widget){}
    // if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        GtkWidget *login_menu = get_widget_by_name_r(main_window, "login_menu");
        gtk_widget_destroy(GTK_WIDGET(login_menu));
        build_signup_menu();
    // }
}

void focus_out_username_field(GtkWidget *widget, gpointer data)
{
    // GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *username_field = get_widget_by_name_r(main_window, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(main_window, "username_notify_label");
    validate_name_field(username_field, username_notify_label);
}

void focus_out_password_field(GtkWidget *widget, gpointer data)
{
    // GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(main_window, "password_notify_label");
    validate_password_field(password_field, password_notify_label);
}

void focus_out_repassword_field(GtkWidget *widget, gpointer data)
{
    // GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *repassword_field = get_widget_by_name_r(main_window, "repassword_field");
    GtkWidget *repassword_notify_label = get_widget_by_name_r(main_window, "repassword_notify_label");
    validate_repassword_field(password_field, repassword_field, repassword_notify_label);
}

void signup_button_click(GtkWidget *widget, gpointer data)
{
    // GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *username_field = get_widget_by_name_r(main_window, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(main_window, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(main_window, "password_notify_label");
    GtkWidget *repassword_field = get_widget_by_name_r(main_window, "repassword_field");
    GtkWidget *repassword_notify_label = get_widget_by_name_r(main_window, "repassword_notify_label");
    GtkWidget *signup_notify_label = get_widget_by_name_r(main_window, "signup_notify_label");

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

	int response_code = handle_signup_request(user_name, user_password);
    handle_signup_response_code(response_code, signup_notify_label);
}

void login_button_click(GtkWidget *widget, gpointer data)
{
    // GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *username_field = get_widget_by_name_r(main_window, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(main_window, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(main_window, "password_notify_label");
    GtkWidget *login_notify_label = get_widget_by_name_r(main_window, "login_notify_label");

    bool username_field_is_empty = is_empty_field(username_field, username_notify_label);
    bool password_field_is_empty = is_empty_field(password_field, password_notify_label);

    if (username_field_is_empty || password_field_is_empty)
	{
        return;
	}

	char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field)));
	char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));

    int response_code = handle_login_request(user_name, user_password);
    handle_login_response_code(response_code, login_notify_label);
}
