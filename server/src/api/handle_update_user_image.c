#include "../../inc/server.h"

void recv_image_from_client(int *socket, unsigned char **buffer, size_t length) {
    unsigned char *ptr = *buffer;
    while (length > 0) {
        int i = recv(*socket, ptr, length, 0);
        ptr += i;
        length -= i;
    }
}

// void handle_update_user_image(const cJSON* data, t_server_utils* utils){
    
//     // Get id of user to update avatar
//     int user_id = cJSON_GetObjectItem(data, "user_id")->valueint;

//     // Get len of encoded image 
//     int len_encoded = 0;
//     usleep(500000);
//     recv(utils->user->client_fd, &len_encoded, sizeof(int), 0);
//     //printf("%d\n", len_encoded);
    
//     // Get encoded image 
//     unsigned char *encoded = malloc(len_encoded);
//     mx_memset(encoded, 0, len_encoded);
//     recv_image_from_client(&utils->user->client_fd, &encoded, len_encoded);
//     //printf("%s\n", encoded);

//     // Decode received image
//     unsigned int flen = b64d_size(len_encoded);
//     unsigned char *decoded = malloc( (sizeof(char) * flen) );
//     memset(decoded, 0, flen);
//     flen = b64_decode(encoded, len_encoded, decoded);
//     free(encoded);

//     // Write to database
//     sqlite3 *db = open_database();
//     sqlite3_stmt *pStmt;
//     char *sql = malloc(flen + 40);
//     bzero(sql, flen + 40);
//     sprintf(sql, "UPDATE `users` SET `image` = ? WHERE `id` = %d;", user_id);
    
//     int rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
    
//     if (rc != SQLITE_OK){
//         char error[100];
//         sprintf(error, "Error while preparing statement: %s\n", sqlite3_errmsg(db));
//         logger(error, ERROR_LOG);
//     }

//     sqlite3_bind_blob(pStmt, 1, decoded, flen, SQLITE_STATIC);
//     rc = sqlite3_step(pStmt);
//     if (rc != SQLITE_DONE) {
//         char error[100];
//         sprintf(error, "execution failed: %s\n", sqlite3_errmsg(db));
//         logger(error, ERROR_LOG);
//     }
//     sqlite3_finalize(pStmt);    
//     sqlite3_close(db);
//     free(sql);
//     free(decoded);
// }
