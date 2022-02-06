#include "../../inc/server.h"

t_response_code db_edit_message(const cJSON* msg_json, t_server_utils* utils) {

    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *new_text = cJSON_GetObjectItemCaseSensitive(msg_json, "text");
    if (!cJSON_IsNumber(message_id) || !cJSON_IsString(new_text)) {
        return R_JSON_FAILURE;
    }

    if (!is_strlen_valid(new_text->valuestring, MIN_MSG_INPUT_LEN, MAX_MSG_INPUT_LEN)) {
        return R_MSG_LEN_INVALID;
    }

    char query[QUERY_LEN];
    sprintf(query, "UPDATE `messages` SET `text` = ? WHERE `id` = '%d' AND `user_id` = '%d' AND `chat_id` = '%d'", 
        message_id->valueint, utils->user->user_id, chat_id->valueint);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, new_text->valuestring, -1, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

void handle_edit_message(const cJSON* message_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_MESSAGE);
        return;
    }

    t_response_code resp_code = 0;
    if ((resp_code = db_edit_message(message_info, utils) != R_SUCCESS)) {
        send_server_response(utils->ssl, resp_code, REQ_EDIT_MESSAGE);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_MESSAGE);
}
