#include "../../inc/client.h"

static void login_or_password_is_invalid(GtkWidget *login_notify_label)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(login_notify_label);
    GtkWidget *username_field = get_widget_by_name_r(toplevel, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(toplevel, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(toplevel, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(toplevel, "password_notify_label");

    set_field_error_style(username_field);
    set_notify_error_style(username_notify_label, "Login or password is invalid");
    set_field_error_style(password_field);
    set_notify_error_style(password_notify_label, "Login or password is invalid");
}

void handle_login_error_code(int error_code, GtkWidget *login_notify_label)
{
    switch (error_code)
    {
        case R_SUCCESS:
            set_notify_success_style(login_notify_label, "You are successful loginned!");
            break;

        case R_INVALID_INPUT:
            set_notify_error_style(login_notify_label, get_response_str(R_INVALID_INPUT));
            break;
        
        case R_USR_NOENT:
            login_or_password_is_invalid(login_notify_label);
            break;
        
        case R_INVALID_PASS:
            login_or_password_is_invalid(login_notify_label);
            break;
        
        default:
            break;
    }
}

void handle_signup_error_code(int error_code, GtkWidget *signup_notify_label)
{
    switch (error_code)
    {
        case R_SUCCESS:
            set_notify_success_style(signup_notify_label, "You are successful registered!");
			break;

        case R_INVALID_INPUT:
            set_notify_error_style(signup_notify_label, get_response_str(R_INVALID_INPUT));
            break;
        
        case R_USR_EXISTS:
            set_notify_error_style(signup_notify_label, get_response_str(R_USR_EXISTS));
            break;
        
        default:
            break;
    }
}

void handle_create_chat_error_code(int error_code, GtkWidget* entry_field, GtkWidget *create_chat_notify_label)
{
    switch (error_code)
    {
        case R_SUCCESS:
            set_notify_success_style(create_chat_notify_label, "");
            break;

        case R_CHAT_EXISTS:
            set_field_error_style(entry_field);
            set_notify_error_style(create_chat_notify_label, get_response_str(R_CHAT_EXISTS));
            break;
        
        default:
            break;
    }
}
