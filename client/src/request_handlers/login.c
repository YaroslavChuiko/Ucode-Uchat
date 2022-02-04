#include "../../inc/client.h"

void set_current_user(t_user** user, const cJSON* user_json) {

    const cJSON* id_json = cJSON_GetObjectItem(user_json, "id");
    const cJSON* name_json = cJSON_GetObjectItemCaseSensitive(user_json, "username");
    const cJSON* pass_json = cJSON_GetObjectItemCaseSensitive(user_json, "password");
    const cJSON* color_json = cJSON_GetObjectItem(user_json, "avatar_color");

    if (!cJSON_IsNumber(id_json) || !cJSON_IsString(name_json) || 
        !cJSON_IsString(pass_json) || !cJSON_IsNumber(color_json)) {
        return;
    }

    *user = malloc(sizeof(t_user));
    (*user)->user_id = id_json->valueint;
    (*user)->name = mx_strdup(name_json->valuestring);
    (*user)->password = mx_strdup(pass_json->valuestring);
    (*user)->avatar_color = color_json->valueint;

}

t_response_code handle_login_response(const char* response_str) {

    if (response_str == NULL)
        return R_INVALID_INPUT;

    cJSON* json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    if (error_code != R_SUCCESS) {
        cJSON_Delete(json);
        return error_code;
    }

    pthread_mutex_lock(&utils->lock);
    set_current_user(&utils->current_user, json);
    pthread_mutex_unlock(&utils->lock);

    if (utils->current_user == NULL) {
        cJSON_Delete(json);
        return R_JSON_FAILURE; 
    }

    cJSON_Delete(json);
    return R_SUCCESS;

}

t_response_code handle_login_request(const char* user_name, const char* user_password) {

    utils->is_suspended = true;
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", user_name);
    cJSON_AddStringToObject(json, "password", user_password);
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGIN);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    
    char* response = send_and_recv_from_server(utils->ssl, json_str);

    t_response_code error_code = handle_login_response(response);
    
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    if (error_code == R_SUCCESS) {

        handle_get_chats_request();
        // handle_get_user_image();
        utils->log_name = get_log_name();
    
    }

    free(json_str);
    free(response);

    utils->is_suspended = false;
    return error_code;
}
