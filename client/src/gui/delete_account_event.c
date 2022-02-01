#include "../../inc/client.h"

void delete_account_btn_click(GtkWidget *widget, gpointer data) {
    if (widget){};

    if (handle_delete_account_request() == R_SUCCESS) {
        client_cleanup(false);
        build_authorizatioin_window();
    }

}
