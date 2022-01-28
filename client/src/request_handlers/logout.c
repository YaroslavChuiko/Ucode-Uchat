#include "../../inc/client.h"

void handle_logout_request(bool is_client_exit) {

    utils->is_suspended = true;

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGOUT);
    cJSON_AddNumberToObject(json, "client_exit", true);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    send_to_server(utils->ssl, json_str);

    free(json_str);
    utils->is_suspended = false;

}
