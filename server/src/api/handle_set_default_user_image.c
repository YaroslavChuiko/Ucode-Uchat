#include "../../inc/server.h"

void handle_set_default_user_image(char *path, int id) {
    // Open file to read
    int r;
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        logger("Cannot open image file\n", ERROR_LOG);    
    }     
    
    // Get len of file
    fseek(fp, 0, SEEK_END);
    if (ferror(fp)) {
        logger("fseek() failed\n", ERROR_LOG); 
        if ((r = fclose(fp)) == EOF) {
            logger("Cannot close file\n", ERROR_LOG);            
        }    
    }  
    
    int flen = ftell(fp);
    if (flen == -1) {
        logger("ftell() error", ERROR_LOG); 
        if ((r = fclose(fp)) == EOF) {
            logger("Cannot close file\n", ERROR_LOG); 
        }   
    }
   
    fseek(fp, 0, SEEK_SET);
    if (ferror(fp)) {
        logger("fseek() failed\n", ERROR_LOG); 
        if ((r = fclose(fp)) == EOF) {
            logger("Cannot close file\n", ERROR_LOG); 
        }    
    }
    
    // Read data of image
    char *data = malloc(flen + 1);
    int size = fread(data, 1, flen, fp);
    if (ferror(fp)) {
        logger("fread() failed\n", ERROR_LOG); 
        if ((r = fclose(fp)) == EOF) {
            logger("Cannot close file\n", ERROR_LOG); 
        }    
    }
    
    if ((r = fclose(fp)) == EOF) {
        logger("Cannot close file\n", ERROR_LOG); 
    }    
    
    // Open database
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        char error[100];
        sprintf(error, "Cannot open database: %s\n", sqlite3_errmsg(db));
        logger(error, ERROR_LOG);
        sqlite3_close(db);
    }
    
    // Write image to database
    sqlite3_stmt *pStmt;
    char *sql = malloc((unsigned)flen + 500);
    bzero(sql, (unsigned)flen + 500);
    sprintf(sql, "UPDATE `users` SET `image` = ? WHERE `id` = '%d' ;", id);
    
    rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK) {
        char error[100];
        sprintf(error, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        logger(error, ERROR_LOG);
    }

    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);    
    rc = sqlite3_step(pStmt);
    if (rc != SQLITE_DONE) {
        char error[100];
        sprintf(error, "Execution failed: %s", sqlite3_errmsg(db));
        logger(error, ERROR_LOG);
    }  

    sqlite3_finalize(pStmt);    
    sqlite3_close(db);
    free(sql);
    free(data);
}
