#include "../../inc/server.h"

t_response_code db_add_user(const cJSON* user_info, t_server_utils* utils) {

    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password");
    const cJSON *avatar_color = cJSON_GetObjectItem(user_info, "avatar_color");
    
    if (!cJSON_IsString(user_name) || !cJSON_IsString(user_password) || !cJSON_IsNumber(avatar_color)) {
        return R_JSON_FAILURE;
    }

    if (db_user_exists(user_name->valuestring)) {
        return R_USR_EXISTS;
    }

    // if (!is_strlen_valid(user_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN)) {
    //     return R_NAME_LEN_INVALID;
    // }
    // if (!is_strlen_valid(user_password->valuestring, MIN_PASS_INPUT_LEN, MAX_PASS_INPUT_LEN)) {
    //     return R_PASS_LEN_INVALID;
    // }

    if (!is_user_name_format_valid(user_name->valuestring)) {
        return R_NAME_FORMAT_INVALID;
    }

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `users` (`username`, `password`, `avatar_color`) VALUES('%s', '%s', '%d')", 
            user_name->valuestring, user_password->valuestring, avatar_color->valueint);
    
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

    int error_code = 0;
    if ((error_code = db_add_user(user_info, utils)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_USR_SIGNUP);
        return;
    }
    
    send_server_response(utils->ssl, R_SUCCESS, REQ_USR_SIGNUP);

}
