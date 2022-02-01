#include "../../inc/server.h"

t_response_code db_delete_user(int user_id) {

    if (!db_get_username_by_id(user_id)) {
        return R_USR_NOENT;
    }

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `users` WHERE `id` = '%d'", user_id);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return R_SUCCESS;

}

t_response_code db_delete_member_by_user_id(int user_id) {
    
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `members` WHERE `user_id` = '%d'", user_id);
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    
    return R_SUCCESS;

}

static t_response_code db_delete_messages(int user_id) {

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `user_id` = '%d'", user_id);
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return R_SUCCESS;

}

void handle_delete_account(const cJSON* chat_info, t_server_utils* utils) {

    (void)chat_info;
    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_ACCOUNT);
        return;
    }

    int error_code = 0;
    if ((error_code = db_delete_user(utils->user->user_id)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
    }
    
    if ((error_code = db_delete_member_by_user_id(utils->user->user_id)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
    }

    if ((error_code = db_delete_messages(utils->user->user_id)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_ACCOUNT);

    logger("User has been removed\n", INFO_LOG);
    client_cleanup(utils, false);

}
