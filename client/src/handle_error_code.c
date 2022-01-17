#include "../inc/client.h"

static void login_or_password_is_invalid()
{
    add_class(t_auth_fields.username_field, "field_error");
    remove_class(t_auth_fields.username_notify_label, "notify_label--success");
    add_class(t_auth_fields.username_notify_label, "notify_label--error");
    gtk_label_set_text(GTK_LABEL(t_auth_fields.username_notify_label), "Login or password is invalid");

    add_class(t_auth_fields.password_field, "field_error");
    remove_class(t_auth_fields.password_notify_label, "notify_label--success");
    add_class(t_auth_fields.password_notify_label, "notify_label--error");
    gtk_label_set_text(GTK_LABEL(t_auth_fields.password_notify_label), "Login or password is invalid");
}

void handle_login_error_code(int error_code)
{
    switch (error_code)
    {
        case R_SUCCESS:
            remove_class(t_auth_fields.result_notify_label, "notify_label--error");
            add_class(t_auth_fields.result_notify_label, "notify_label--success");
            gtk_label_set_text(GTK_LABEL(t_auth_fields.result_notify_label), "You are successful loginned!");
            break;

        case R_INVALID_INPUT:
            remove_class(t_auth_fields.result_notify_label, "notify_label--success");
            add_class(t_auth_fields.result_notify_label, "notify_label--error");
            gtk_label_set_text(GTK_LABEL(t_auth_fields.result_notify_label), get_response_str(R_INVALID_INPUT));
            break;
        
        case R_USR_NOENT:
            login_or_password_is_invalid();
            break;
        
        case R_INVALID_PASS:
            login_or_password_is_invalid();
            break;
        
        default:
            break;
    }
}

void handle_signup_error_code(int error_code)
{
    switch (error_code)
    {
        case R_SUCCESS:
            remove_class(t_auth_fields.result_notify_label, "notify_label--error");
            add_class(t_auth_fields.result_notify_label, "notify_label--success");
            gtk_label_set_text(GTK_LABEL(t_auth_fields.result_notify_label), "You are successful registered!");
			break;

        case R_INVALID_INPUT:
            remove_class(t_auth_fields.result_notify_label, "notify_label--success");
            add_class(t_auth_fields.result_notify_label, "notify_label--error");
            gtk_label_set_text(GTK_LABEL(t_auth_fields.result_notify_label), get_response_str(R_INVALID_INPUT));
            break;
        
        case R_USR_EXISTS:
            remove_class(t_auth_fields.result_notify_label, "notify_label--success");
            add_class(t_auth_fields.result_notify_label, "notify_label--error");
            gtk_label_set_text(GTK_LABEL(t_auth_fields.result_notify_label), get_response_str(R_USR_EXISTS));
            break;
        
        default:
            break;
    }
}

void handle_create_chat_error_code(int error_code, GtkWidget* entry_field)
{
    switch (error_code)
    {
        case R_SUCCESS:
            remove_class(entry_field, "field_error");
            add_class(entry_field, "field_success");
            break;

        case R_CHAT_EXISTS:
            remove_class(entry_field, "field_success");
            add_class(entry_field, "field_error");
            break;
        
        default:
            break;
    }
}
