#include "../../inc/client.h"

t_chat* handle_search_chats_request(const char* search_str) {

    utils->is_suspended = true;
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "search_pattern", search_str);
    cJSON_AddNumberToObject(json, "type", REQ_SEARCH_CHATS);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    int error_code = 0;
    char* response = send_and_recv_from_server(utils->ssl, json_str);
    free(json_str);

    t_chat* chat_list = NULL;
    if ((error_code = handle_get_chats_response(&chat_list, response, true)) != R_SUCCESS) {
        logger(get_response_str(error_code), ERROR_LOG);
        free(response);
        utils->is_suspended = false;
        return NULL;
    }
    free(response);

    utils->is_suspended = false;
    return chat_list;

}
