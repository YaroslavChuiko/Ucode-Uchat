#include "../../inc/client.h"

t_msg* get_msg_from_json(cJSON* json) {

    cJSON* msg_id = cJSON_GetObjectItem(json, "msg_id");
    cJSON* sender_id = cJSON_GetObjectItem(json, "sender_id");
    cJSON* sender_name = cJSON_GetObjectItemCaseSensitive(json, "sender_name");
    cJSON* text = cJSON_GetObjectItemCaseSensitive(json, "text");
    cJSON* chat_id = cJSON_GetObjectItem(json, "chat_id");
    cJSON* date = cJSON_GetObjectItemCaseSensitive(json, "date");

    if (!cJSON_IsNumber(msg_id) || !cJSON_IsNumber(sender_id) || !cJSON_IsNumber(chat_id) || 
        !cJSON_IsString(sender_name) || !cJSON_IsString(text) || !cJSON_IsNumber(date)) {

        return NULL;
    }

    return mx_create_msg(msg_id->valueint, sender_id->valueint, sender_name->valuestring, chat_id->valueint, 
                        text->valuestring, mx_get_string_time(date->valueint));

}

t_msg* handle_get_msg_response() {

    char* response_str = recv_from_server(utils->ssl);

    if (response_str == NULL) {
        return NULL;
    }

    cJSON* json = cJSON_Parse(response_str);

    int error_code = get_response_code(json);
    if (error_code != R_SUCCESS) {
        printf("not success -- %d\n", error_code);
        cJSON_Delete(json);
        logger(get_response_str(error_code), ERROR_LOG);
        return NULL;
    }
    cJSON* msg_json = cJSON_GetObjectItem(json, "message");
    t_msg* new_msg = get_msg_from_json(msg_json);

    if (new_msg == NULL || new_msg->sender_id == utils->current_user->user_id) {
        printf("not valid msg\n");
        cJSON_Delete(json);
        logger(get_response_str(R_JSON_FAILURE), ERROR_LOG);
        return NULL;
    }
    
    cJSON_Delete(json);
    free(response_str);
    return new_msg;

}

void handle_get_msg_request(int chat_id, int message_id) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_GET_MSG);
    cJSON_AddNumberToObject(json, "message_id", message_id);
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    send_to_server(utils->ssl, json_str);
    free(json_str);

}
