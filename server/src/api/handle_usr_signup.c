#include "../../inc/server.h"

t_response_code db_add_user(const char* user_name, const char* password) {

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `users` (`username`, `password`) VALUES('%s', '%s')", 
        user_name, password);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return R_SUCCESS;

}

void handle_usr_signup(const cJSON* user_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_SIGNUP);
        return;
    }
    
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

    // if (!is_strlen_valid(user_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN)) {
    //     send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_USR_SIGNUP);
    //     return;
    // }
    // if (!is_strlen_valid(user_password->valuestring, MIN_PASS_INPUT_LEN, MAX_PASS_INPUT_LEN)) {
    //     send_server_response(utils->ssl, R_PASS_LEN_INVALID, REQ_USR_SIGNUP);
    //     return;
    // }
    
    if (!is_user_name_format_valid(user_name->valuestring)) {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_USR_SIGNUP);
        return;
    }

    int error_code = 0;
    if ((error_code = db_add_user(user_name->valuestring, user_password->valuestring)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_USR_SIGNUP);
        return;
    }
    
    handle_set_default_user_image("default_image.png", db_get_id_by_username(user_name->valuestring));

    send_server_response(utils->ssl, R_SUCCESS, REQ_USR_SIGNUP);

}
