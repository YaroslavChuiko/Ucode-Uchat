#include "../../inc/client.h"

static void edit_global_messages(int message_id) {

    bool is_last_msg = message_id == utils->current_chat->last_new_msg->message_id;
    mx_msg_pop_id(&utils->current_chat->messages, message_id);
    if (is_last_msg) {
        if (mx_msg_list_size(utils->current_chat->messages) == 0) {
            utils->current_chat->last_new_msg = NULL;
        } else {
            utils->current_chat->last_new_msg = mx_get_last_msg_node(utils->current_chat->messages);
        }
        update_chatlist_item_info(utils->current_chat);
    }

}

void handle_delete_msg_request(int message_id) {

    utils->is_suspended = true;

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_MESSAGE);
    cJSON_AddNumberToObject(json, "id", message_id);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);
    int error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    if (error_code == R_SUCCESS) {
        
        edit_global_messages(message_id);

    }

    free(json_str);
    free(response);
    utils->is_suspended = false;

}
