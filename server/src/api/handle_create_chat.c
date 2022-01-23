#include "../../inc/server.h"

void handle_create_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_CREATE_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    if (!cJSON_IsString(chat_name))    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_CREATE_CHAT);
        return;
    }

    if (!is_user_name_format_valid(chat_name->valuestring)) {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_CREATE_CHAT);
        return;
    }

    t_response_code resp_code = 0;
    if ((resp_code = db_insert_chat(chat_name->valuestring)) != R_SUCCESS) {
        send_server_response(utils->ssl, resp_code, REQ_CREATE_CHAT);
        return;
    }
    
    if (db_insert_member(chat_name->valuestring, ADMIN_MEMBER, utils) != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_CREATE_CHAT);
        return;
    }
    
    send_server_response(utils->ssl, R_SUCCESS, REQ_CREATE_CHAT);

    print_logged_users();
    
}
