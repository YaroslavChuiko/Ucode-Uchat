#include "../../inc/client.h"

t_chat* get_chat_from_json(cJSON* json) {

    cJSON* chat_id = cJSON_GetObjectItem(json, "chat_id");
    cJSON* chat_name = cJSON_GetObjectItemCaseSensitive(json, "chat_name");
    cJSON* chat_perms = cJSON_GetObjectItem(json, "chat_permissions");

    if (!cJSON_IsNumber(chat_id) || !cJSON_IsString(chat_name) || !cJSON_IsNumber(chat_perms)) {
        return NULL;
    }

    t_chat* chat = mx_create_chat(chat_id->valueint, chat_name->valuestring, chat_perms->valueint);
    return chat;

}

t_chat* handle_get_chat_response(const char* response_str) {

    if (response_str == NULL) {
        logger(get_response_str(R_INVALID_INPUT), ERROR_LOG);
        return NULL;
    }

    cJSON* json = cJSON_Parse(response_str);
    t_chat* gotten_chat = NULL;

    int error_code = get_response_code(json);
    if (error_code != R_SUCCESS) {
        logger(get_response_str(error_code), ERROR_LOG);
        cJSON_Delete(json);
        return NULL;
    }

    if (!(gotten_chat = get_chat_from_json(json))) {
        logger(get_response_str(R_JSON_FAILURE), ERROR_LOG);
        cJSON_Delete(json);
        return NULL;
    }
    cJSON_Delete(json);
    return gotten_chat;

}

t_response_code handle_get_chat_request(const char* chat_name) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHAT);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);
    t_chat* gotten_chat = NULL;
    free(json_str);

    if (!(gotten_chat = handle_get_chat_response(response))) {
        logger("Couldn't load chat", ERROR_LOG);
        free(response);
        return R_CHAT_NOENT;
    }
    free(response);

    char str[200];
    sprintf(str, "Gotten chat:\n\tid: %d, name: %s, perms: %d\n", 
            gotten_chat->id, gotten_chat->name, gotten_chat->permissions);
    logger(str, INFO_LOG);

    return R_SUCCESS;
}
