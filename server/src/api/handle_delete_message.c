#include "../../inc/server.h"

t_response_code db_delete_message(const cJSON* msg_json, t_server_utils* utils) {

    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    if (!cJSON_IsNumber(message_id)) {
        return R_JSON_FAILURE;
    }

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `id` = '%d' AND `user_id` = '%d' AND `chat_id` = '%d'", 
        message_id->valueint, utils->user->user_id, utils->user->chats->id);
    
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

    // validation here later
    t_response_code resp_code = 0;
    if ((resp_code = db_delete_message(message_info, utils) != R_SUCCESS)) {
        send_server_response(utils->ssl, resp_code, REQ_DELETE_MESSAGE);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_MESSAGE);
}
