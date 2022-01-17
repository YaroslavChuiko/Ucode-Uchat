#include "../../inc/client.h"

bool is_empty_username(char *user_name)
{
    if (!mx_strcmp(user_name, ""))
    {
        add_class(t_auth_fields.username_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.username_notify_label), "This field is required!");
		return true;
    }
    else
    {
        remove_class(t_auth_fields.username_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.username_notify_label), "");
		return false;
    }
}

bool is_empty_password(char *user_password)
{
    if (!mx_strcmp(user_password, ""))
    {
        add_class(t_auth_fields.password_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.password_notify_label), "This field is required!");
		return true;
    }
    else
    {
        remove_class(t_auth_fields.password_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.password_notify_label), "");
		return false;
    }
}

bool check_valid_username(char *username)
{
    if (!mx_strcmp(username, ""))
    {
        add_class(t_auth_fields.username_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.username_notify_label), "Fill the username please!"); //This field is required!
		return false;
    }
    else if (mx_strlen(username) < 1) //4
    {
        add_class(t_auth_fields.username_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.username_notify_label), "Username length must be atleast 4 characters");
		return false;
    }
    else if (mx_strlen(username) > 15)
    {
        add_class(t_auth_fields.username_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.username_notify_label), "Username length must not exceed 15 characters");
		return false;
    }
    else
    {
        add_class(t_auth_fields.username_field, "field_success");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.username_notify_label), "");
		return true;
    }
}

bool check_valid_password(char *user_password)
{
    if (!mx_strcmp(user_password, ""))
    {
        add_class(t_auth_fields.password_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.password_notify_label), "Fill the password please!");
		return false;
    }
    else if (mx_strlen(user_password) < 1) //8
    {
        add_class(t_auth_fields.password_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.password_notify_label), "Password length must be atleast 8 characters");
		return false;
    }
    else if (mx_strlen(user_password) > 15)
    {
        add_class(t_auth_fields.password_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.password_notify_label), "Password length must not exceed 15 characters");
		return false;
    }
    else
    {
        add_class(t_auth_fields.password_field, "field_success");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.password_notify_label), "");
		return true;
    }
}

bool check_valid_repassword(char *user_password, char *user_repassword)
{
    if (!mx_strcmp(user_repassword, ""))
    {
        add_class(t_auth_fields.repassword_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.repassword_notify_label), "Fill the password please!");
		return false;
    }
    else if (mx_strcmp(user_password, user_repassword))
	{
		add_class(t_auth_fields.repassword_field, "field_error");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.repassword_notify_label), "Passwords do not match!");
		return false;
	}
    else
    {
        add_class(t_auth_fields.repassword_field, "field_success");
        gtk_label_set_text(GTK_LABEL(t_auth_fields.repassword_notify_label), "");
		return true;
    }
}
