#include "../../inc/client.h"

void modify_global_user(const char* new_name, const char* new_pass) {

    t_user* curr_user = utils->current_user;
    if (new_name) {
        mx_strdel(&curr_user->name);
        curr_user->name = mx_strdup(new_name);
    }
    if (new_pass) {
        mx_strdel(&curr_user->password);
        curr_user->password = mx_strdup(new_pass);
    }

}

t_response_code handle_edit_username_request(const char* new_name) {

    utils->is_suspended = true;

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", new_name);
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_USERNAME);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);

    t_response_code error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    if (error_code == R_SUCCESS) {

        modify_global_user(new_name, NULL);

    }

    free(json_str);
    free(response);

    utils->is_suspended = false;
    return error_code;
}

t_response_code handle_edit_password_request(const char* new_pass, const char* old_pass) {

    utils->is_suspended = true;

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "new_password", new_pass);
    cJSON_AddStringToObject(json, "old_password", old_pass);
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_PASSWORD);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);

    t_response_code error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    if (error_code == R_SUCCESS) {

        modify_global_user(NULL, new_pass);

    }

    free(json_str);
    free(response);

    utils->is_suspended = false;
    return error_code;
}
