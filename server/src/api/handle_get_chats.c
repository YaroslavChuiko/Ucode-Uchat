#include "../../inc/server.h"

// Get a single chat in JSON format
cJSON* get_chat_json(sqlite3_stmt* stmt) {

    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", sqlite3_column_int64(stmt, 0));
    cJSON_AddStringToObject(json, "chat_name", (const char*)sqlite3_column_text(stmt, 1));
    cJSON_AddNumberToObject(json, "chat_permissions", sqlite3_column_int64(stmt, 2));
    return json;

}

// Get chats array in JSON format
cJSON* get_chats_array_json(int user_id) {

    cJSON* chats_json = cJSON_CreateArray();
    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, members.permissions FROM chats"
                            " INNER JOIN `members` ON members.chat_id = chats.id"
                            " WHERE chats.id IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) AND members.user_id = ?",
                            -1, &stmt, NULL);
                            
    sqlite3_bind_int64(stmt, 1, user_id);
    sqlite3_bind_int64(stmt, 2, user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        cJSON_AddItemToArray(chats_json, get_chat_json(stmt));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chats_json;
    
}

/*  Handle a request for getting all the chats in which
    the logged in user participates
*/ 
void handle_get_chats(const cJSON* chat_info, t_server_utils* utils) {

    (void)chat_info;

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS);
        return;
    }

    cJSON* json = cJSON_CreateObject();
    cJSON* chats = get_chats_array_json(utils->user->user_id);
    cJSON_AddItemReferenceToObject(json, "chats", chats);
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHATS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    
    char* json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    
    cJSON_Delete(json);
    free(json_str);

}
