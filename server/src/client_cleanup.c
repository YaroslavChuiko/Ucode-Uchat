#include "../inc/server.h"

void client_cleanup(t_server_utils* utils) {

    SSL_free(utils->ssl);
    close(utils->client_socket);
    mx_clear_user(&utils->user);
    free(utils);

    logger("Cleanup completed\n", INFO_LOG);

}
