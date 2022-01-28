#include "../inc/server.h"

void client_cleanup(t_server_utils* utils, bool is_client_exit) {

    mx_clear_user(&utils->user);
    if (is_client_exit) {
        SSL_free(utils->ssl);
        close(utils->client_socket);
        free(utils);
    }

    logger("Cleanup completed\n", INFO_LOG);

}
