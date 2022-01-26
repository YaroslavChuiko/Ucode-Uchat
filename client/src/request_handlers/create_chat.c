#include "../../inc/client.h"

t_response_code handle_create_chat_request(const char* chat_name) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_CREATE_CHAT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);

    t_response_code error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    if (error_code == R_SUCCESS) {

        handle_get_chats_request();

    }

    free(json_str);
    free(response);

    return error_code;
}
