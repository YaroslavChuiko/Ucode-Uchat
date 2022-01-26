#include "../../inc/client.h"

t_response_code add_chat_to_chatlist(cJSON* json, t_chat** chat_list) {

    cJSON* chat_id = cJSON_GetObjectItem(json, "chat_id");
    cJSON* chat_name = cJSON_GetObjectItemCaseSensitive(json, "chat_name");
    cJSON* chat_perms = cJSON_GetObjectItem(json, "chat_permissions");

    if (!cJSON_IsNumber(chat_id) || !cJSON_IsString(chat_name) || !cJSON_IsNumber(chat_perms)) {
        return R_JSON_FAILURE;
    }
    mx_chat_push_back(chat_list, chat_id->valueint, chat_name->valuestring, chat_perms->valueint);

    // Fill current chat's messages' list with all existing messages
    handle_get_chat_msgs_request(chat_id->valueint);

    return R_SUCCESS;

}

t_response_code handle_get_chats_response(t_chat** chat_list, const char* response_str) {

    if (response_str == NULL) {
        return R_INVALID_INPUT;
    }

    cJSON* json = cJSON_Parse(response_str);

    int error_code = get_response_code(json);
    if (error_code != R_SUCCESS) {
        cJSON_Delete(json);
        return error_code;
    }

    cJSON* chats_array = cJSON_GetObjectItemCaseSensitive(json, "chats");
    if (!cJSON_IsArray(chats_array)) {
        cJSON_Delete(json);
        return R_JSON_FAILURE;
    }

    mx_clear_chat_list(chat_list);
    
    cJSON* chat = NULL;
    for (int i = 0; i < cJSON_GetArraySize(chats_array); ++i) {
        
        chat = cJSON_GetArrayItem(chats_array, i);
        if ((error_code = add_chat_to_chatlist(chat, chat_list)) != R_SUCCESS) {
            cJSON_Delete(json);
            return error_code;
        }
    
    }
    cJSON_Delete(json);
    return R_SUCCESS;

}

t_response_code handle_get_chats_request() {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHATS);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    int error_code = 0;
    char* response = send_and_recv_from_server(utils->ssl, json_str);
    free(json_str);

    if ((error_code = handle_get_chats_response(&utils->chatlist, response)) != R_SUCCESS) {
        logger(get_response_str(error_code), ERROR_LOG);
        free(response);
        return error_code;
    }
    free(response);

    mx_print_chat_list(utils->chatlist);

    return R_SUCCESS;

}
