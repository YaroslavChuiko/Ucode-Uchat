#include "../../inc/server.h"

void user_cleanup(t_user** user) {

    if (!user || !(*user))
        return;

    mx_strdel(&(*user)->name);
    mx_strdel(&(*user)->password);
    free(*user);
    *user = NULL;

}

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
        utils->user->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        utils->user->password = strdup((const char*)sqlite3_column_text(stmt, 2));

    }
    sqlite3_finalize(stmt);

}

int set_user_by_username(const char* username, const char* password, t_server_utils* utils) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT * FROM `users` WHERE `username` = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, NULL);

    set_user_account_data(stmt, utils);
    sqlite3_close(db);

    if (utils->user == NULL) {
        send_server_response(utils->ssl, R_USR_NOENT, REQ_USR_LOGIN);
        return 1;
    } 
    if (strcmp(utils->user->password, password) != 0) {
        send_server_response(utils->ssl, R_INVALID_PASS, REQ_USR_LOGIN);
        user_cleanup(&utils->user);
        return 1;
    }
    
    char* response = get_json_formatted_user(utils->user);
    send_response_to(utils->ssl, response);
    free(response);
    
    char result_to_log[QUERY_LEN];
    sprintf(result_to_log, "Logged in user info: id: %d, name: %s", 
            utils->user->user_id, 
            utils->user->name);

    logger(result_to_log, INFO_LOG);
    return 0;

}

void handle_usr_login(const cJSON* user_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_LOGIN);
        return;
    }

    // validation here later
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password");

    if (!cJSON_IsString(user_name) || !cJSON_IsString(user_password)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_LOGIN);
        return;
    }

    if (set_user_by_username(user_name->valuestring, user_password->valuestring, utils) != 0)
        return;

    pthread_mutex_lock(&global_state.lock);
    mx_user_push_back(&global_state.logged_users, utils->user->user_id, utils->user->client_fd, utils->ssl);
    pthread_mutex_unlock(&global_state.lock);

    print_logged_users();

}
