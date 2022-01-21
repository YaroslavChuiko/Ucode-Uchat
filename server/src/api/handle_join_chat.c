#include "../../inc/server.h"

void handle_join_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_JOIN_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_name");
    int chat_id = db_get_chat_id_by_name(chat_name->valuestring);

    if (!cJSON_IsString(chat_name))    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_JOIN_CHAT);
        return;
    }
    if (chat_id == -1) {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_JOIN_CHAT);
        return;
    }
    if (db_is_chat_member(utils->user->user_id, chat_id)) {
        send_server_response(utils->ssl, R_IS_CHAT_MEMBER, REQ_JOIN_CHAT);
        return;
    }

    t_response_code resp_code = 0;
    if ((resp_code = db_insert_member(chat_name->valuestring, NORMAL_MEMBER, utils)) != R_SUCCESS) {
        send_server_response(utils->ssl, resp_code, REQ_JOIN_CHAT);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_JOIN_CHAT);

    print_logged_users();

}
