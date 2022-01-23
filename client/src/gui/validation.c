#include "../../inc/client.h"

bool is_empty_field(GtkWidget *field, GtkWidget *notify_label)
{
	char *text = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(field)));

    if (!mx_strcmp(text, ""))
    {
        set_field_error_style(field);
        set_notify_error_style(notify_label, "This field is required!");
		return true;
    }
    else
    {
        remove_class(field, "input_field--error");
        set_notify_error_style(notify_label, "");
		return false;
    }
}

bool validate_name_field(GtkWidget *username_field, GtkWidget *username_notify_label)
{
	char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field)));

    if (!mx_strcmp(user_name, ""))
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, "Fill the name please!");
		return false;
    }
    else if (mx_strlen(user_name) < 1) //4
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, "The name length must be atleast 4 characters");
		return false;
    }
    else if (mx_strlen(user_name) > 15)
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, "the name length must not exceed 15 characters");
		return false;
    }
    else if (!is_user_name_format_valid(user_name))
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, get_response_str(R_NAME_FORMAT_INVALID));
		return false;
    }
    else
    {
        set_field_success_style(username_field);
        set_notify_success_style(username_notify_label, "");
		return true;
    }
}

bool validate_password_field(GtkWidget *password_field, GtkWidget *password_notify_label)
{
	char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));

    if (!mx_strcmp(user_password, ""))
    {
        set_field_error_style(password_field);
        set_notify_error_style(password_notify_label, "Fill the password please!");
		return false;
    }
    else if (mx_strlen(user_password) < 1) //8
    {
        set_field_error_style(password_field);
        set_notify_error_style(password_notify_label, "Password length must be atleast 8 characters");
		return false;
    }
    else if (mx_strlen(user_password) > 15)
    {
        set_field_error_style(password_field);
        set_notify_error_style(password_notify_label, "Password length must not exceed 15 characters");
		return false;
    }
    else
    {
        set_field_success_style(password_field);
        set_notify_success_style(password_notify_label, "");
		return true;
    }
}

bool validate_repassword_field(GtkWidget *password_field, GtkWidget *repassword_field, GtkWidget *repassword_notify_label)
{
    char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));
	char *user_repassword = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(repassword_field)));

    if (!mx_strcmp(user_repassword, ""))
    {
        set_field_error_style(repassword_field);
        set_notify_error_style(repassword_notify_label, "Fill the password please!");
		return false;
    }
    else if (mx_strcmp(user_password, user_repassword))
	{
        set_field_error_style(repassword_field);
        set_notify_error_style(repassword_notify_label, "Passwords do not match!");
		return false;
	}
    else
    {
        set_field_success_style(repassword_field);
        set_notify_success_style(repassword_notify_label, "");
		return true;
    }
}
