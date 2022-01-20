#include "../../inc/client.h"

void handle_logout_request() {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGOUT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);

    int error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(json_str);
    free(response);

}

void handle_client_exit() {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_CLIENT_EXIT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    send_to_server(utils->ssl, json_str);

    free(json_str);

}
