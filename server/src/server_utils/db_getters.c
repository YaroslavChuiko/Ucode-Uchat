#include "../../inc/server.h"

t_chat* db_get_chats_by_user_id(int user_id) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT * FROM `chats` WHERE `id` IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?)", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, user_id);

    t_chat* chats = NULL;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int chat_id = sqlite3_column_int64(stmt, 0);
        const char* chat_name = (const char*)sqlite3_column_text(stmt, 1);
        mx_chat_push_back(&chats, chat_id, chat_name);

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chats;

}

t_user* db_get_user_by_id(int user_id) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT * FROM `users` WHERE `id` = ?", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, user_id);

    t_user* user = NULL;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        user = mx_create_user(user_id, -1);
        user->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        user->password = strdup((const char*)sqlite3_column_text(stmt, 2));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user;

}
