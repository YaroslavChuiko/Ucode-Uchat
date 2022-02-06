#include "../inc/server.h"

sqlite3* open_database() {

    sqlite3* db;
    if (sqlite3_open(DB_NAME, &db)) {
        logger(strerror(errno), ERROR_LOG);
        return NULL;
    }
    return db;

}

// Create all the needed tables if they don't exist
int database_init() {

    struct stat info;
    if (stat(DB_NAME, &info) == 0) {
        return 0;
    }

    sqlite3* db = open_database();
    
    char* query = 
        "CREATE TABLE `users` ("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
            "`username` VARCHAR(32) NOT NULL,"
            "`password` VARCHAR(32) NOT NULL,"
            "`avatar_color` TINYINT NOT NULL,"
            "`image` BLOB);"

        "CREATE TABLE `chats` ("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT," 
            "`name` VARCHAR(32) NOT NULL,"
            "`date` INTEGER NOT NULL,"
            "`avatar_color` TINYINT NOT NULL);"
        
        "CREATE TABLE `members` ("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT," 
            "`user_id` INTEGER NOT NULL," 
            "`chat_id` INTEGER NOT NULL,"
            "`permissions` INTEGER NOT NULL);"
            
        "CREATE TABLE `messages` ("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT," 
            "`user_id` INTEGER NOT NULL," 
            "`chat_id` INTEGER NOT NULL,"
            "`text` VARCHAR(1024) NOT NULL,"
            "`date` INTEGER NOT NULL);";
    
    char* errmsg;
    if (sqlite3_exec(db, query, NULL, NULL, &errmsg)) {
        logger(errmsg, ERROR_LOG);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;

}

// Execute a singe sqlite statement, without finalizing it (yet)
sqlite3_stmt* db_execute_stmt_for(const char* query, sqlite3* db) {

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_step(stmt);
    return stmt;

}

int db_execute_query(const char* query) {

    sqlite3* db = open_database();

    char* errmsg;
    if (sqlite3_exec(db, query, NULL, NULL, &errmsg)) {
        logger(errmsg, ERROR_LOG);
        return 1;
    }
    sqlite3_close(db);
    return 0;

}
