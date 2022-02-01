#include "../../inc/client.h"

void leave_chat_btn_click(GtkWidget *widget, gpointer data) {

    int response_code = handle_leave_chat_request(utils->current_chat->name);

    if (response_code == R_SUCCESS)
    {
        utils->current_chat = NULL;
        update_chatlist();
        // build_start_messaging_label();
    }

}

