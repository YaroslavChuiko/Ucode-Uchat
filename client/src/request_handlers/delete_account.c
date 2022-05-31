#include "../../inc/client.h"

t_response_code handle_delete_account_request() {

    utils->is_suspended = true;

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_ACCOUNT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);
    int error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(json_str);
    free(response);
    return error_code;
}
