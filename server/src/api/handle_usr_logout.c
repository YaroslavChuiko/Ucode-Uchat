#include "../../inc/server.h"

void handle_usr_logout(const cJSON* user_info, t_server_utils* utils) {

    cJSON* user_id = cJSON_GetObjectItem(user_info, "user_id");
    if (!cJSON_IsNumber(user_id)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_LOGOUT);
        return;
    }
    int user_list_id = mx_get_user_id(user_id->valueint);
    printf("user list id -- %d & db id -- %d\n", user_list_id, user_id->valueint);
    mx_user_pop_index(&global_state.logged_users, user_list_id);

    send_server_response(utils->ssl, R_SUCCESS, REQ_USR_LOGOUT);

    print_logged_users();

    // cleanup and exit the thread here

}
