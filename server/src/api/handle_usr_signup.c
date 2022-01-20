#include "../../inc/server.h"

bool db_user_exists(const char* username) {

    char query[QUERY_LEN];
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `users` WHERE `username` = '%s')", username);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    int user_exists = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user_exists == 1;

}

void handle_usr_signup(const cJSON* user_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_SIGNUP);
        return;
    }
    
    // validation here later
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password");
    
    if (!cJSON_IsString(user_name) || !cJSON_IsString(user_password)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_SIGNUP);
        return;
    }

    if (db_user_exists(user_name->valuestring)) {
        send_server_response(utils->ssl, R_USR_EXISTS, REQ_USR_SIGNUP);
        return;
    }

    if (!is_name_format_valid(user_name->valuestring)) {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_USR_SIGNUP);
        return;
    }

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `users` (`username`, `password`) VALUES('%s', '%s')", 
        user_name->valuestring, user_password->valuestring);
    
    if (db_execute_query(query) != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_SIGNUP);
        return;
    }
    send_server_response(utils->ssl, R_SUCCESS, REQ_USR_SIGNUP);

}
