#include "../../inc/server.h"

t_response_code db_insert_message(const cJSON* msg_json, t_msg** msg_to_send, t_server_utils* utils) {

    const cJSON *user_id = cJSON_GetObjectItem(msg_json, "user_id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *message = cJSON_GetObjectItemCaseSensitive(msg_json, "text");
    if (!cJSON_IsNumber(user_id) || !cJSON_IsNumber(chat_id) || !cJSON_IsString(message)) {
        return R_JSON_FAILURE;
    }

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `messages` (`user_id`, `chat_id`, `text`) VALUES('%d', '%d', '%s')", 
        user_id->valueint, chat_id->valueint, message->valuestring);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }

    *msg_to_send = mx_create_msg(message->valuestring, user_id->valueint, chat_id->valueint, utils);

    return R_SUCCESS;

}

char* get_new_message_json(t_msg* msg_to_send) {

    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_NEW_MESSAGE);
    cJSON_AddNumberToObject(json, "chat_id", msg_to_send->chat_id);
    cJSON_AddStringToObject(json, "text", msg_to_send->text);
    cJSON_AddNumberToObject(json, "sender_id", msg_to_send->sender->user_id);
    cJSON_AddStringToObject(json, "sender_name", msg_to_send->sender->name);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return json_str;

}

void handle_send_message(const cJSON* message_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_SEND_MESSAGE);
        return;
    }

    // validation here later
    t_response_code resp_code = 0;
    t_msg* msg_to_send = NULL;
    if ((resp_code = db_insert_message(message_info, &msg_to_send, utils)) != R_SUCCESS) {
        send_server_response(utils->ssl, resp_code, REQ_SEND_MESSAGE);
        return;
    }

    if (!msg_to_send || !msg_to_send->sender) {
        send_server_response(utils->ssl, R_MSG_USR_NOENT, REQ_SEND_MESSAGE);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_SEND_MESSAGE);
    send_response_to_all(msg_to_send);

}
