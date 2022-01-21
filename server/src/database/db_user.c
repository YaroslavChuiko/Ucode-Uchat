#include "../../inc/server.h"

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
