#include "../../inc/server.h"

bool db_chat_exists(const char* chat_name) {

    char query[QUERY_LEN];
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `chats` WHERE `name` = '%s')", chat_name);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    int chat_exists = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chat_exists == 1;

}

t_response_code db_insert_chat(const char* chat_name) {

    if (db_chat_exists(chat_name)) {
        return R_CHAT_EXISTS;
    }

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `chats` (`name`) VALUES('%s')", chat_name);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return 0;

}

int db_insert_member(const char* chat_name, t_server_utils* utils) {

    char query[QUERY_LEN];
    sprintf(query, "SELECT `id` FROM `chats` WHERE `name` = '%s'", chat_name);

    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);

    int user_id = utils->user->user_id;
    int chat_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    bzero(query, QUERY_LEN);

    sprintf(query, "INSERT INTO `members` (`user_id`, `chat_id`) VALUES('%d', '%d')", user_id, chat_id);
    if (db_execute_query(query) != 0) {
        return 1;
    }
    mx_chat_push_back(&utils->user->chats, chat_id, chat_name);
    t_user* user_to_update = NULL;
    if ((user_to_update = mx_get_user_by_id(global_state.logged_users, user_id))) {
        mx_chat_push_back(&user_to_update->chats, chat_id, chat_name);
    }
    
    return 0;

}

void handle_create_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->client_socket, R_DB_FAILURE, REQ_CREATE_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    if (!cJSON_IsString(chat_name))    {
        send_server_response(utils->client_socket, R_JSON_FAILURE, REQ_CREATE_CHAT);
        return;
    }

    t_response_code resp_code = 0;
    if ((resp_code = db_insert_chat(chat_name->valuestring)) != R_SUCCESS) {
        send_server_response(utils->client_socket, resp_code, REQ_CREATE_CHAT);
        return;
    }
    
    if (db_insert_member(chat_name->valuestring, utils) != 0) {
        send_server_response(utils->client_socket, R_DB_FAILURE, REQ_CREATE_CHAT);
        return;
    }
    
    send_server_response(utils->client_socket, R_SUCCESS, REQ_CREATE_CHAT);

    print_logged_users();
    
}
