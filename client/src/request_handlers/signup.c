#include "../../inc/client.h"

t_response_code handle_signup_response(const char* response_str) {

    cJSON* json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    cJSON_Delete(json);
    return error_code;   

}


t_response_code handle_signup_request(const char* user_name, const char* user_password) {

    utils->is_suspended = true;
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", user_name);
    cJSON_AddStringToObject(json, "password", user_password);
    cJSON_AddNumberToObject(json, "type", REQ_USR_SIGNUP);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);

    t_response_code error_code = handle_signup_response(response);
            
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(json_str);
    free(response);

    utils->is_suspended = false;
	return error_code;

}
