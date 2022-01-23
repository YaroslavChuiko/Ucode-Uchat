#include "../../inc/client.h"

int handle_delete_chat_request(const char* chat_name) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_CHAT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    printf("name: %s \n", chat_name);

    char* response = send_and_recv_from_server(utils->ssl, json_str);

    int error_code = handle_server_response(response);
    // if ((error_code = handle_server_response(response)) != R_SUCCESS) {

        // Here, if server responded with error, notify the user via the GUI
        logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // }
    free(json_str);
    free(response);

    return error_code;
}