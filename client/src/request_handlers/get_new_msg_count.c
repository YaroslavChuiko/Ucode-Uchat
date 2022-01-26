#include "../../inc/client.h"

t_response_code get_new_msg_count_response(const char* response_str, int* i_last_msg_id) {

    if (response_str == NULL) {
        logger("in get_new_msg_count_response", ERROR_LOG);
        return R_INVALID_INPUT;
    }

    cJSON* json = cJSON_Parse(response_str);

    int error_code = get_response_code(json);
    if (error_code != R_SUCCESS) {
        cJSON_Delete(json);
        return error_code;
    }

    cJSON* last_msg_id = cJSON_GetObjectItem(json, "last_msg_id");
    if (!cJSON_IsNumber(last_msg_id)) {
        return R_JSON_FAILURE;
    }
    *i_last_msg_id = last_msg_id->valueint;
    cJSON_Delete(json);
    return R_SUCCESS;

}

int handle_new_msg_count_request(int chat_id, bool is_current) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddNumberToObject(json, "type", REQ_NEW_MSG_COUNT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    
    int error_code = 0;
    char* response = send_and_recv_from_server(utils->ssl, json_str);
    free(json_str);

    int last_msg_id = 0;
    if ((error_code = get_new_msg_count_response(response, &last_msg_id)) != R_SUCCESS) {
        logger(get_response_str(error_code), ERROR_LOG);
        free(response);
        return -1;
    }
    free(response);

    t_chat* current_chat = mx_get_chat_by_id(utils->chatlist, chat_id);
    int last_client_msg_id = mx_get_last_msg_id(current_chat, is_current);

    return last_msg_id - last_client_msg_id;

}
