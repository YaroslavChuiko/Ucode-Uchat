#include "../../inc/client.h"

t_response_code add_msg_to_msglist(cJSON* json) {

    cJSON* msg_id = cJSON_GetObjectItem(json, "msg_id");
    cJSON* sender_id = cJSON_GetObjectItem(json, "sender_id");
    cJSON* sender_name = cJSON_GetObjectItemCaseSensitive(json, "sender_name");
    cJSON* text = cJSON_GetObjectItemCaseSensitive(json, "text");
    cJSON* chat_id = cJSON_GetObjectItem(json, "chat_id");
    cJSON* date = cJSON_GetObjectItemCaseSensitive(json, "date");

    if (!cJSON_IsNumber(msg_id) || !cJSON_IsNumber(sender_id) || !cJSON_IsNumber(chat_id) || 
        !cJSON_IsString(sender_name) || !cJSON_IsString(text) || !cJSON_IsNumber(date)) {

        return R_JSON_FAILURE;
    }
    t_chat* chat_by_id = mx_get_chat_by_id(utils->chatlist, chat_id->valueint);
    if (!chat_by_id)
        return R_CHAT_NOENT;

    mx_msg_dfl_push_back(&chat_by_id->messages, msg_id->valueint, sender_id->valueint, sender_name->valuestring,
                    chat_id->valueint, text->valuestring, mx_get_string_time(date->valueint));

    if (sender_id->valueint == utils->current_user->user_id) {
        return R_SUCCESS;
    }

    if (chat_by_id->last_new_msg)
		mx_clear_msg(&chat_by_id->last_new_msg);

	chat_by_id->last_new_msg = mx_create_msg(msg_id->valueint, sender_id->valueint, sender_name->valuestring, 
											chat_id->valueint, text->valuestring, mx_get_string_time(date->valueint));

    return R_SUCCESS;

}

t_response_code handle_get_chat_msgs_response(const char* response_str) {

    if (response_str == NULL) {
        return R_INVALID_INPUT;
    }

    cJSON* json = cJSON_Parse(response_str);

    int error_code = get_response_code(json);
    if (error_code != R_SUCCESS) {
        return error_code;
        cJSON_Delete(json);
    }

    cJSON* msg_array = cJSON_GetObjectItemCaseSensitive(json, "messages");
    if (!cJSON_IsArray(msg_array)) {
        cJSON_Delete(json);
        return R_JSON_FAILURE;
    }
    
    cJSON* chat = NULL;
    for (int i = 0; i < cJSON_GetArraySize(msg_array); ++i) {
        
        chat = cJSON_GetArrayItem(msg_array, i);
        if ((error_code = add_msg_to_msglist(chat)) != R_SUCCESS) {
            cJSON_Delete(json);
            return error_code;
        }
    
    }
    cJSON_Delete(json);
    return R_SUCCESS;

}

t_response_code handle_get_chat_msgs_request(int chat_id) {

    utils->is_suspended = true;

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHAT_MSGS);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    int error_code = 0;
    char* response = send_and_recv_from_server(utils->ssl, json_str);
    free(json_str);

    if ((error_code = handle_get_chat_msgs_response(response)) != R_SUCCESS) {
        logger(get_response_str(error_code), ERROR_LOG);
        free(response);
        utils->is_suspended = false;
        return error_code;
    }
    free(response);
    utils->is_suspended = false;
    return R_SUCCESS;

}
