#include "../../inc/server.h"

int get_last_msg_id(const cJSON* chat_info, t_server_utils* utils) {

    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    if (!cJSON_IsNumber(chat_id))    {
        return -1;
    }

    char query[QUERY_LEN];
    sprintf(query, "SELECT id FROM `messages` WHERE chat_id = %d AND NOT user_id = %d ORDER BY id DESC LIMIT 1", 
            chat_id->valueint, utils->user->user_id);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    int last_msg_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return last_msg_id;

}

void handle_new_msg_count(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_NEW_MSG_COUNT);
        return;
    }
    int last_msg_id = -1;
    if ((last_msg_id = get_last_msg_id(chat_info, utils)) == -1) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_NEW_MSG_COUNT);
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
