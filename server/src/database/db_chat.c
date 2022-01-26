#include "../../inc/server.h"

t_response_code db_insert_chat(const char* chat_name, int date) {

    int chat_id = db_get_chat_id_by_name(chat_name);
    if (chat_id != -1) {
        return R_CHAT_EXISTS;
    }

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `chats` (`name`, `date`) VALUES('%s', '%d')", chat_name, date);
    
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

t_chat* db_get_chats_by_user_id(int user_id) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, chats.permissions FROM `chats` WHERE `id` IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?)", 
                        -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, user_id);

    t_chat* chats = NULL;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int chat_id = sqlite3_column_int64(stmt, 0);
        const char* chat_name = (const char*)sqlite3_column_text(stmt, 1);
        int permissions = sqlite3_column_int64(stmt, 2);
        mx_chat_push_back(&chats, chat_id, chat_name, permissions);

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chats;

}


