#include "../../inc/server.h"

char* get_json_formatted_user(const t_user* user) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGIN);
    cJSON_AddNumberToObject(json, "id", user->user_id);
    cJSON_AddStringToObject(json, "username", user->name);
    cJSON_AddStringToObject(json, "password", user->password);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    char* user_info = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return user_info;

}

void set_user_account_data(sqlite3_stmt* stmt, t_server_utils* utils) {

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        utils->user = mx_create_user(sqlite3_column_int64(stmt, 0), utils->client_socket, utils->ssl);
        utils->user->name = mx_strdup((const char*)sqlite3_column_text(stmt, 1));
        utils->user->password = mx_strdup((const char*)sqlite3_column_text(stmt, 2));

    }
    sqlite3_finalize(stmt);

}

t_response_code set_user_by_username(const char* username, const char* password, t_server_utils* utils) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT * FROM `users` WHERE `username` = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, NULL);

    set_user_account_data(stmt, utils);
    sqlite3_close(db);

    if (utils->user == NULL) {
        return R_USR_NOENT;
    } 
    if (strcmp(utils->user->password, password) != 0) {
        mx_clear_user(&utils->user);
        return R_INVALID_PASS;
    }
    
    char* response = get_json_formatted_user(utils->user);
    send_response_to(utils->ssl, response);
    free(response);
    
    char result_to_log[QUERY_LEN];
    sprintf(result_to_log, "Logged in user info: id: %d, name: %s", 
            utils->user->user_id,
            utils->user->name);

    logger(result_to_log, INFO_LOG);
    return R_SUCCESS;

}

void handle_usr_login(const cJSON* user_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_LOGIN);
        return;
    }

    int error_code = 0;
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password");

    if (!cJSON_IsString(user_name) || !cJSON_IsString(user_password)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_LOGIN);
        return;
    }

    if ((error_code = set_user_by_username(user_name->valuestring, 
                                        user_password->valuestring, utils)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_USR_LOGIN);
    }

}
