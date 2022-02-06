#include "../../inc/client.h"

t_response_code add_to_global_msglist(t_msg* new_msg) {

    t_chat* curr_chat = mx_get_chat_by_id(utils->chatlist, new_msg->chat_id);
    if (!curr_chat) {
        return R_CHAT_NOENT;
    }

    // new_msg->avatar_path = mx_strdup(utils->current_user->avatar_path);
    mx_msg_push_back(&curr_chat->messages, new_msg);
    curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->messages);
    update_chatlist_item_info(curr_chat);
    return R_SUCCESS;
    
}

t_response_code handle_send_msg_response(const char* response_str, t_msg* sent_msg) {

    if (response_str == NULL)
        return R_INVALID_INPUT;

    cJSON* json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    if (error_code != R_SUCCESS) {
        mx_clear_msg(&sent_msg);
        cJSON_Delete(json);
        return error_code;
    }

    cJSON* msg_id = cJSON_GetObjectItem(json, "message_id");
    sent_msg->message_id = msg_id->valueint;

    if ((error_code = add_to_global_msglist(sent_msg)) != R_SUCCESS) {
        return error_code;
    }

    cJSON_Delete(json);
    return R_SUCCESS;

}

t_response_code handle_send_msg_request(const char* message_str) {

    utils->is_suspended = true;
    
    unsigned long curr_time = get_current_time();
    t_msg* sent_msg = mx_create_msg(-1, utils->current_user->user_id, utils->current_user->name,
                                    utils->current_chat->id, message_str, get_string_time(curr_time));

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_SEND_MESSAGE);
    cJSON_AddStringToObject(json, "text", sent_msg->text);
    cJSON_AddNumberToObject(json, "user_id", sent_msg->sender_id);
    cJSON_AddStringToObject(json, "user_name", sent_msg->sender_name);
    cJSON_AddNumberToObject(json, "chat_id", sent_msg->chat_id);
    cJSON_AddNumberToObject(json, "date", curr_time);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);
    int error_code = handle_send_msg_response(response, sent_msg);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(response);
    utils->is_suspended = false;
    return error_code;

}
