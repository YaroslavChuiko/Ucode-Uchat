#include "../../inc/server.h"

t_response_code db_delete_chat(const char* chat_name) {

    if (!db_chat_exists(chat_name)) {
        return R_CHAT_NOENT;
    }

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `chats` WHERE `name` = '%s'", chat_name);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return 0;

}

int db_delete_member(int chat_id, t_server_utils* utils) {
    
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `members` WHERE `chat_id` = '%d'", chat_id);
    if (db_execute_query(query) != 0) {
        return 1;
    }
    
    mx_chat_pop_id(&utils->user->chats, chat_id);
    t_user* user_to_update = NULL;
    if ((user_to_update = mx_get_user_by_id(global_state.logged_users, utils->user->user_id))) {
        mx_chat_pop_id(&user_to_update->chats, chat_id);
    }

    return 0;

}

int db_delete_messages(int chat_id, t_server_utils* utils) {

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `chat_id` = '%d'", chat_id);
    if (db_execute_query(query) != 0) {
        return 1;
    }

    return 0;

}

int get_chat_id(const char* chat_name) {
    char query[QUERY_LEN];
    sprintf(query, "SELECT `id` FROM `chats` WHERE `name` = '%s'", chat_name);

    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);

    int chat_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chat_id;
}

void handle_delete_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    if (!cJSON_IsString(chat_name))    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_DELETE_CHAT);
        return;
    }

    int chat_id = get_chat_id(chat_name->valuestring);
    t_response_code resp_code = 0;
    if ((resp_code = db_delete_chat(chat_name->valuestring)) != R_SUCCESS) {
        send_server_response(utils->ssl, resp_code, REQ_DELETE_CHAT);
        return;
    }
    
    if (db_delete_member(chat_id, utils) != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT);
        return;
    }

    if (db_delete_messages(chat_id, utils) != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT);
        return;
    }
    
    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_CHAT);

    print_logged_users();
    
}
