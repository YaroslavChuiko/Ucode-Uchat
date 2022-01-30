#include "../../inc/server.h"

t_response_code db_modify_user_name(int user_id, const char* new_name) {

    char query[QUERY_LEN];
    sprintf(query, "UPDATE `users` SET `username` = '%s' WHERE `id` = '%d'", new_name, user_id);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return R_SUCCESS;

}

t_response_code db_modify_password(int user_id, const char* password) {

    char query[QUERY_LEN];
    sprintf(query, "UPDATE `users` SET `password` = '%s' WHERE `id` = '%d'", password, user_id);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return R_SUCCESS;

}

void handle_edit_username(const cJSON* user_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_USERNAME);
        return;
    }
    
    const cJSON *new_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");
    
    if (!cJSON_IsString(new_name)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_EDIT_USERNAME);
        return;
    }

    int error_code = 0;
    if (db_user_exists(new_name->valuestring)) {
        send_server_response(utils->ssl, R_USR_EXISTS, REQ_EDIT_USERNAME);
        return;
    }

    // if (!is_strlen_valid(new_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN)) {
    //     send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_EDIT_USERNAME);
    //     return;
    // }

    if (!is_user_name_format_valid(new_name->valuestring)) {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_EDIT_USERNAME);
        return;
    }

    if ((error_code = db_modify_user_name(utils->user->user_id, new_name->valuestring)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_EDIT_USERNAME);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_USERNAME);

}

void handle_edit_password(const cJSON* pass_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_PASSWORD);
        return;
    }

    int error_code = 0;
    const cJSON *new_pass = cJSON_GetObjectItemCaseSensitive(pass_info, "new_password");
    const cJSON *old_pass = cJSON_GetObjectItemCaseSensitive(pass_info, "old_password");

    if (!cJSON_IsString(new_pass) || !cJSON_IsString(old_pass)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_EDIT_PASSWORD);
        return;
    }

    if (strcmp(utils->user->password, old_pass->valuestring) != 0) {
        send_server_response(utils->ssl, R_INVALID_PASS, REQ_EDIT_PASSWORD);
        return;
    }

    // if (!is_strlen_valid(new_pass->valuestring, MIN_PASS_INPUT_LEN, MAX_PASS_INPUT_LEN)) {
    //     send_server_response(utils->ssl, R_PASS_LEN_INVALID, REQ_EDIT_PASSWORD);
    //     return;
    // }

    if ((error_code = db_modify_password(utils->user->user_id, new_pass->valuestring)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_EDIT_PASSWORD);
        return;
    }
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_PASSWORD);

}
