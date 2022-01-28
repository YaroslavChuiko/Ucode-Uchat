#include "../../inc/client.h"

void logout_btn_click(GtkWidget *widget, gpointer data)
{
    if (widget){};
    
    handle_logout_request(false);
	client_cleanup(false);
    build_authorizatioin_window();
}
