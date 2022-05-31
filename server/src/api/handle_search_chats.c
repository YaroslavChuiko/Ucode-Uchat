#include "../../inc/server.h"

// Get chats array in JSON format
cJSON* get_search_chats_array(const cJSON* chat_info, t_server_utils* utils) {

    cJSON* search_pattern = cJSON_GetObjectItemCaseSensitive(chat_info, "search_pattern");
    if (!cJSON_IsString(search_pattern)) {
        return NULL;
    }

    cJSON* chats_json = cJSON_CreateArray();
    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    char* search_str = mx_strnew(mx_strlen(search_pattern->valuestring) + 4);
    mx_strcat(search_str, "%%");
    mx_strcat(search_str, search_pattern->valuestring);
    mx_strcat(search_str, "%%");
    sqlite3_prepare_v2(db,  "SELECT chats.id, chats.name, chats.avatar_color FROM chats "
                            "WHERE chats.name LIKE ? "
                            "AND chats.id NOT IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) "
                            "ORDER BY chats.date DESC ",
                            -1, &stmt, NULL);
                            
    sqlite3_bind_text(stmt, 1, search_str, -1, NULL);
    sqlite3_bind_int64(stmt, 2, utils->user->user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        cJSON_AddItemToArray(chats_json, get_chat_json(stmt, true));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    mx_strdel(&search_str);
    return chats_json;
    
}

/*  Handle a request for getting all the chats
    whose names match the search pattern
*/ 
void handle_search_chats(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS);
        return;
    }

    cJSON* json = cJSON_CreateObject();
    cJSON* chats = get_search_chats_array(chat_info, utils);
    cJSON_AddItemReferenceToObject(json, "chats", chats);
    cJSON_AddNumberToObject(json, "type", REQ_SEARCH_CHATS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    
    char* json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    
    cJSON_Delete(json);
    free(json_str);

}
