#include "../../inc/server.h"

static t_response_code db_delete_member(int user_id, int chat_id) {
    
    if (!db_chat_exists(chat_id)) {
        return R_CHAT_NOENT;
    }

    if (!db_is_chat_member(user_id, chat_id)) {
        return R_ISNT_CHAT_MEMBER;
    }

    if (!db_has_chat_perms(user_id, chat_id, NORMAL_MEMBER)) {
        return R_NO_CHAT_PERMS;
    }

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    
    return R_SUCCESS;

}

void handle_leave_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_LEAVE_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    if (!cJSON_IsString(chat_name))    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_LEAVE_CHAT);
        return;
    }

    int chat_id = db_get_chat_id_by_name(chat_name->valuestring);
    int error_code = 0;
    
    if ((error_code = db_delete_member(utils->user->user_id, chat_id)) != 0) {
        send_server_response(utils->ssl, error_code, REQ_LEAVE_CHAT);
        return;
    }
    send_server_response(utils->ssl, R_SUCCESS, REQ_LEAVE_CHAT);
    
}
