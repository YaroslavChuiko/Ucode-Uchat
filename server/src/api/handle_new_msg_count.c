#include "../../inc/server.h"

t_response_code get_last_msg_id(const cJSON* chat_info, t_server_utils* utils, int* last_msg_id) {

    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    if (!cJSON_IsNumber(chat_id)) {
        return R_JSON_FAILURE;
    }

    if (!db_chat_exists(chat_id->valueint)) {
        mx_chat_pop_id(&utils->user->chats, chat_id->valueint);
        return R_CHAT_NOENT;
    }

    char query[QUERY_LEN];
    sprintf(query, "SELECT id FROM `messages` WHERE chat_id = %d AND NOT user_id = %d ORDER BY id DESC LIMIT 1", 
            chat_id->valueint, utils->user->user_id);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    *last_msg_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return R_SUCCESS;

}

void handle_new_msg_count(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_NEW_MSG_COUNT);
        return;
    }
    int last_msg_id = -1;
    int error_code = 0;
    if ((error_code = get_last_msg_id(chat_info, utils, &last_msg_id)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_NEW_MSG_COUNT);
        return;
    }
    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "last_msg_id", last_msg_id);
    cJSON_AddNumberToObject(json, "type", REQ_NEW_MSG_COUNT);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    
    char* json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    
    cJSON_Delete(json);
    free(json_str);

}
