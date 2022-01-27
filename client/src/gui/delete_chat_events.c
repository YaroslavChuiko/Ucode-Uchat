#include "../../inc/client.h"

void delete_chat_btn_click(GtkWidget *widget, gpointer data)
{

    int response_code = handle_delete_chat_request(utils->current_chat->name);
    // handle_create_chat_error_code(error_code, chat_name_field, chat_name_notify_label);

    if (response_code == R_SUCCESS)
    {
        // GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");
        update_chatlist();
        build_start_messaging_label();
        // set_chatlist_item_active(get_widget_by_name_r(chatlist_container, mx_itoa(utils->current_chat->id)));
        // utils->current_chat ? set_chatlist_item_active(get_widget_by_name_r(chatlist_container, utils->current_chat->name)) : (void)0;
        // gtk_widget_destroy(toplevel);
    }
}
