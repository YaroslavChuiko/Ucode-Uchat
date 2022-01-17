#include "../../inc/client.h"

void switch_to_login_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    // if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth_menu.signup_event));
        build_login_menu((GtkWidget**)main_area);
    // }
}

void switch_to_signup_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area)
{
    if(widget){}
    // if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_widget_destroy(GTK_WIDGET(t_auth_menu.login_event));
        build_signup_menu((GtkWidget**)main_area);
    // }
}

void focus_out_username_field(GtkWidget *widget, gpointer data)
{
    if (widget){}
    char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.username_field)));
    check_valid_username(user_name);
}

void focus_out_password_field(GtkWidget *widget, gpointer data)
{
    if (widget){}
    char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.password_field)));
    check_valid_password(user_password);
}

void focus_out_repassword_field(GtkWidget *widget, gpointer data)
{
    if (widget){}
    char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.password_field)));
	char *user_repassword = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.repassword_field)));
    check_valid_repassword(user_password, user_repassword);
}

void signup_button_click(GtkWidget *widget, gpointer main_area)
{
    if(widget){};

	char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.username_field)));
	char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.password_field)));
	char *user_repassword = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.repassword_field)));

	if (!check_valid_username(user_name) || !check_valid_password(user_password) || !check_valid_repassword(user_password, user_repassword))
	{
        // remove_class(t_auth_fields.result_notify_label, "notify_label--success");
        add_class(t_auth_fields.result_notify_label, "notify_label--error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.result_notify_label), "Please fill all fields correctly!");
        return;
	}

	int error_code = handle_signup_request(user_name, user_password);
    handle_signup_error_code(error_code);

    if(error_code == R_SUCCESS)
    {
        gtk_widget_destroy(t_auth_menu.signup_event);
        build_login_menu((GtkWidget**)main_area);
    }
}

void login_button_click(GtkWidget *widget, gpointer main_area)
{
    if(widget){};
    
	char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.username_field)));
	char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(t_auth_fields.password_field)));

    bool username_field_is_empty = is_empty_username(user_name);
    bool password_field_is_empty = is_empty_password(user_password);

    if (username_field_is_empty || password_field_is_empty)
	{
        return;
	}

    int error_code = handle_login_request(user_name, user_password);
    handle_login_error_code(error_code);

	if(error_code == R_SUCCESS)
    {
        gtk_widget_destroy(t_auth_menu.login_event);
        build_chat_screen((GtkWidget**)main_area);
    }
}
