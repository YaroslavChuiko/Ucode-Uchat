#include "../../inc/client.h"

void logout_btn_click(GtkWidget *widget, gpointer data)
{
    handle_logout_request();

    // int response_code = handle_delete_chat_request(utils->current_chat->name);

    // if (response_code == R_SUCCESS)
    // {
    //     update_chatlist();
    //     build_start_messaging_label();
    // }
    build_authorizatioin_window();
}

