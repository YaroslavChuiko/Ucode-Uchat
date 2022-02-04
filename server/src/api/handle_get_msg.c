#include "../../inc/server.h"

static cJSON* get_msg_by_id(const cJSON* msg_info) {

    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(msg_info, "chat_id");
    const cJSON *message_id = cJSON_GetObjectItemCaseSensitive(msg_info, "message_id");

    if (!cJSON_IsNumber(chat_id) || !cJSON_IsNumber(message_id)) {
        return NULL;
    }
    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,  "SELECT messages.id, messages.user_id, users.username, messages.chat_id, messages.text, messages.date "
                            "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                            "WHERE messages.chat_id = ? AND messages.id = ?",
                            -1, &stmt, NULL);
                            
    sqlite3_bind_int64(stmt, 1, chat_id->valueint);
    sqlite3_bind_int64(stmt, 2, message_id->valueint);

    cJSON* message_json = NULL; 
    if (sqlite3_step(stmt) == SQLITE_ROW) {

        message_json = get_msg_json(stmt);

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return message_json;

}

void handle_get_msg(const cJSON* msg_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS);
        return;
    }

    cJSON* msg_json = get_msg_by_id(msg_info);
    
    if (msg_json == NULL) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_MSG);
        return;
    }

    cJSON* json = cJSON_CreateObject();
    cJSON_AddItemReferenceToObject(json, "message", msg_json);
    cJSON_AddNumberToObject(json, "type", REQ_GET_MSG);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    
    char* json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    
    cJSON_Delete(json);
    free(json_str);

}
