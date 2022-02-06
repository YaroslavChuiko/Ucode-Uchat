#include "../../inc/server.h"

void handle_create_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_CREATE_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");
    const cJSON *date = cJSON_GetObjectItem(chat_info, "date");
    const cJSON *av_color = cJSON_GetObjectItem(chat_info, "avatar_color");

    if (!cJSON_IsString(chat_name) || !cJSON_IsNumber(av_color) || !cJSON_IsNumber(date)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_CREATE_CHAT);
        return;
    }

    if (!is_strlen_valid(chat_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN)) {
        send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_CREATE_CHAT);
        return;
    }

    if (!is_user_name_format_valid(chat_name->valuestring)) {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_CREATE_CHAT);
        return;
    }

    if (db_get_chats_total(utils->user->user_id) >= MAX_CHATS_TOTAL) {
        send_server_response(utils->ssl, R_CHATS_TOTAL_REACHED, REQ_CREATE_CHAT);
        return;
    }

    t_response_code resp_code = 0;
    if ((resp_code = db_insert_chat(chat_name->valuestring, date->valueint, av_color->valueint)) != R_SUCCESS) {
        send_server_response(utils->ssl, resp_code, REQ_CREATE_CHAT);
        return;
    }
    
    if (db_insert_member(chat_name->valuestring, ADMIN_MEMBER, utils) != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_CREATE_CHAT);
        return;
    }
    
    send_server_response(utils->ssl, R_SUCCESS, REQ_CREATE_CHAT);
    
}
