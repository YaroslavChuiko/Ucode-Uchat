#include "../../inc/server.h"

t_response_code db_edit_message(const cJSON* msg_json, t_server_utils* utils) {

    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *new_text = cJSON_GetObjectItemCaseSensitive(msg_json, "text");
    if (!cJSON_IsNumber(message_id) || !cJSON_IsString(new_text)) {
        return R_JSON_FAILURE;
    }

    char query[QUERY_LEN];
    sprintf(query, "UPDATE `messages` SET `text` = '%s' WHERE `id` = '%d' AND `user_id` = '%d' AND `chat_id` = '%d'", 
        new_text->valuestring, message_id->valueint, utils->user->user_id, utils->user->chats->id);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }

    return 0;
}

void handle_edit_message(const cJSON* message_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_MESSAGE);
        return;
    }

    // validation here later
    t_response_code resp_code = 0;
    if ((resp_code = db_edit_message(message_info, utils) != R_SUCCESS)) {
        send_server_response(utils->ssl, resp_code, REQ_EDIT_MESSAGE);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_MESSAGE);
}
