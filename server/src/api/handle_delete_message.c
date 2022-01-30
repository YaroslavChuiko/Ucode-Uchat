#include "../../inc/server.h"

t_response_code db_delete_message(const cJSON* msg_json, t_server_utils* utils) {

    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    if (!cJSON_IsNumber(message_id) || !cJSON_IsNumber(chat_id)) {
        return R_JSON_FAILURE;
    }

    if (!db_chat_exists(chat_id->valueint)) {
        return R_CHAT_NOENT;
    }
    if (!db_is_chat_member(utils->user->user_id, chat_id->valueint)) {
        return R_ISNT_CHAT_MEMBER;
    }

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `id` = '%d' AND `chat_id` = '%d'", 
        message_id->valueint, chat_id->valueint);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }

    return 0;
}

void handle_delete_message(const cJSON* message_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_MESSAGE);
        return;
    }

    t_response_code resp_code = 0;
    if ((resp_code = db_delete_message(message_info, utils) != R_SUCCESS)) {
        send_server_response(utils->ssl, resp_code, REQ_DELETE_MESSAGE);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_MESSAGE);
}
