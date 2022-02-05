#include "../../inc/server.h"

bool db_is_chat_member(int user_id, int chat_id) {

    char query[QUERY_LEN];
    sprintf(query, 
            "SELECT EXISTS (SELECT `id` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d')", 
            user_id, chat_id);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    int is_chat_member = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return is_chat_member == 1;

}

int db_insert_member(const char* chat_name, t_member_type member_type, t_server_utils* utils) {

    char query[QUERY_LEN];
    sprintf(query, "SELECT `id` FROM `chats` WHERE `name` = '%s'", chat_name);

    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);

    int user_id = utils->user->user_id;
    int chat_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    bzero(query, QUERY_LEN);

    sprintf(query, 
            "INSERT INTO `members` (`user_id`, `chat_id`, `permissions`) VALUES('%d', '%d', '%d')", 
            user_id, chat_id, member_type);

    if (db_execute_query(query) != 0) {
        return 1;
    }
    
    return 0;

}
