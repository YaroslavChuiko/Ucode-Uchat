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

static void build_chat_window()
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

void handle_login_response_code(int response_code, GtkWidget *login_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(login_notify_label, "You are successful loginned!");
            build_chat_window();
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

void handle_signup_response_code(int response_code, GtkWidget *signup_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(signup_notify_label, "You are successful registered!");
            GtkWidget *signup_menu = get_widget_by_name_r(main_window, "signup_menu");
            GtkWidget *main_area = get_widget_by_name_r(main_window, "main_area");
            gtk_widget_destroy(signup_menu);
            build_login_menu(&main_area);
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

void handle_create_chat_response_code(int response_code, GtkWidget* entry_field, GtkWidget *create_chat_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(create_chat_notify_label, "");

            GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");
            GtkWidget *toplevel = gtk_widget_get_toplevel(entry_field);
            update_chatlist();
            utils->current_chat ? set_chatlist_item_active(get_widget_by_name_r(chatlist_container, utils->current_chat->name)) : (void)0;
            gtk_widget_destroy(toplevel);
            break;

        case R_CHAT_EXISTS:
            set_field_error_style(entry_field);
            set_notify_error_style(create_chat_notify_label, get_response_str(R_CHAT_EXISTS));
            break;
        
        default:
            break;
    }
}

void handle_join_chat_response_code(int response_code, char *chat_name)
{
    switch (response_code)
    {
        case R_SUCCESS:
            update_chatlist();
            GtkWidget *new_chatlist_item = get_widget_by_name_r(main_window, chat_name);
            activate_chat(new_chatlist_item);
            break;

        case R_CHAT_NOENT:
            build_chatlist_message(get_response_str(R_CHAT_NOENT));
            break;

        case R_IS_CHAT_MEMBER:
            build_chatlist_message(get_response_str(R_IS_CHAT_MEMBER));
            break;
        
        default:
            break;
    }
}
