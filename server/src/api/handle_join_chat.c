#include "../../inc/server.h"

void handle_join_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->client_socket, R_DB_FAILURE, REQ_JOIN_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_name");

    if (!cJSON_IsString(chat_name))    {
        send_server_response(utils->client_socket, R_JSON_FAILURE, REQ_JOIN_CHAT);
        return;
    }
    if (!db_chat_exists(chat_name->valuestring)) {
        send_server_response(utils->client_socket, R_CHAT_NOENT, REQ_JOIN_CHAT);
        return;
    }

    // validation here later
    t_response_code resp_code = 0;
    if ((resp_code = db_insert_member(chat_name->valuestring, utils)) != R_SUCCESS) {
        send_server_response(utils->client_socket, resp_code, REQ_JOIN_CHAT);
        return;
    }

    send_server_response(utils->client_socket, R_SUCCESS, REQ_JOIN_CHAT);

    print_logged_users();

}
