#include "../../inc/server.h"

t_response_code db_insert_chat(const char* chat_name, int date, int avatar_color) {

    int chat_id = db_get_chat_id_by_name(chat_name);
    if (chat_id != -1) {
        return R_CHAT_EXISTS;
    }

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `chats` (`name`, `date`, `avatar_color`) VALUES('%s', '%d', '%d')", 
            chat_name, date, avatar_color);
    
    if (db_execute_query(query) != 0) {
        return R_DB_FAILURE;
    }
    return 0;

}

bool db_chat_exists(int chat_id) {

    char query[QUERY_LEN];
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `chats` WHERE `id` = '%d')", chat_id);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    int chat_exists = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chat_exists == 1;

}

int db_get_chat_id_by_name(const char* chat_name) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT `id` FROM `chats` WHERE `name` = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, chat_name, -1, NULL);

    int chat_id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {

        chat_id = sqlite3_column_int64(stmt, 0);

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chat_id;

}

bool db_has_chat_perms(int user_id, int chat_id, t_member_type perms) {

    char query[QUERY_LEN];
    sprintf(query, "SELECT `permissions` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    int chat_perms = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return (t_member_type)chat_perms == perms;

}

int db_get_chats_total(int user_id) {

    char query[QUERY_LEN];
    sprintf(query,  "SELECT COUNT(*) FROM chats "
                    "INNER JOIN members ON members.chat_id = chats.id "
                    "WHERE members.user_id IN (%d)", user_id);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    int chat_total = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chat_total;

}
