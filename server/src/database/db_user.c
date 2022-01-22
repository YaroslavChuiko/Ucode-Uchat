#include "../../inc/server.h"

bool db_user_exists(const char* username) {

    char query[QUERY_LEN];
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `users` WHERE `username` = '%s')", username);
    
    sqlite3* db = open_database();
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    
    int user_exists = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user_exists == 1;

}

char* db_get_username_by_id(int user_id) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT `name` FROM `users` WHERE `id` = ?", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, user_id);
    
    char* user_name = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) {

        user_name = strdup((const char*)sqlite3_column_text(stmt, 1));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user_name;

}

t_user* db_get_user_by_id(int user_id, t_server_utils* utils) {

    sqlite3* db = open_database();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT * FROM `users` WHERE `id` = ?", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, user_id);

    t_user* user = NULL;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        user = mx_create_user(user_id, -1, utils->ssl);
        user->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        user->password = strdup((const char*)sqlite3_column_text(stmt, 2));

    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user;

}
