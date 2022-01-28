#include "../../inc/server.h"

t_request_type handle_usr_logout(const cJSON* logout_info, t_server_utils* utils) {

    const cJSON *client_exit = cJSON_GetObjectItemCaseSensitive(logout_info, "client_exit");

    if (!cJSON_IsNumber(client_exit)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_LOGOUT);
        return REQ_USR_LOGOUT;
    }
    int is_client_exit = client_exit->valueint;

    printf("client exit -- %d\n", is_client_exit);
    if (utils->user) {
        char str[100];
        sprintf(str, "User (%d, %s) logging out\n", utils->user->user_id, utils->user->name);
        logger(str, INFO_LOG);
    }

    client_cleanup(utils, is_client_exit);
    return is_client_exit ? REQ_CLIENT_EXIT : REQ_USR_LOGOUT;

}
