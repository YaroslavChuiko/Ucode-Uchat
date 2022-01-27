#include "../../inc/server.h"

t_response_code db_insert_message(const cJSON* msg_json, int* message_id, t_server_utils* utils) {

    const cJSON *user_id = cJSON_GetObjectItem(msg_json, "user_id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(msg_json, "user_name");
    const cJSON *message = cJSON_GetObjectItemCaseSensitive(msg_json, "text");
    const cJSON *date = cJSON_GetObjectItemCaseSensitive(msg_json, "date");
    if (!cJSON_IsNumber(user_id) || !cJSON_IsNumber(chat_id) || 
        !cJSON_IsString(user_name) || !cJSON_IsString(message) || !cJSON_IsNumber(date)) {
        
        return R_JSON_FAILURE;
    }
    if (!db_chat_exists(chat_id->valueint)) {
        return R_CHAT_NOENT;
    }
    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `messages` (`user_id`, `chat_id`, `text`, `date`) VALUES('%d', '%d', '%s', '%d')", 
            user_id->valueint, chat_id->valueint, message->valuestring, date->valueint);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    bzero(query, sizeof(query));
    sprintf(query,  "SELECT id FROM `messages` WHERE `user_id` = '%d' AND `chat_id` = '%d' "
                    "ORDER BY `id` DESC LIMIT 1",
            user_id->valueint, chat_id->valueint);
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_step(stmt);
    
    *message_id = sqlite3_column_int64(stmt, 0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return R_SUCCESS;

}

void handle_send_message(const cJSON* message_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_SEND_MESSAGE);
        return;
    }

    // validation here later
    t_response_code resp_code = 0;
    int message_id = 0;
    if ((resp_code = db_insert_message(message_info, &message_id, utils)) != R_SUCCESS) {
        send_server_response(utils->ssl, resp_code, REQ_SEND_MESSAGE);
        return;
    }

    cJSON* json_to_send = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_to_send, "message_id", message_id);
    cJSON_AddNumberToObject(json_to_send, "type", REQ_SEND_MESSAGE);
    cJSON_AddNumberToObject(json_to_send, "error_code", R_SUCCESS);
    char* json_str = cJSON_PrintUnformatted(json_to_send);
    cJSON_Delete(json_to_send);

    send_response_to(utils->ssl, json_str);
    free(json_str);

}
