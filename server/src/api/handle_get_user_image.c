#include "../../inc/server.h"

void send_to_client(int *socket, void *buffer, size_t length) {
    unsigned char *ptr = (unsigned char *)buffer;
    while (length > 0) {
        //usleep(70000);
        int i = send(*socket, ptr, length, 0);
        ptr += i;
        length -= i;
    }
}

// void handle_get_user_image(const cJSON* img_info, t_server_utils* utils) {

//     // Get id of user to receive image
//     int user_id = cJSON_GetObjectItem(img_info, "user_id")->valueint;

//     // Read image from database
//     sqlite3 *db = open_database();
//     char sql[500];
//     bzero(sql, 500);
//     sprintf(sql, "SELECT `image` FROM `users` WHERE `id` = %d;", user_id);
//     sqlite3_stmt *pStmt;

//     int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
//     if (rc != SQLITE_OK ) {
//         fprintf(stderr, "Failed to prepare statement 11111\n");
//         fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
//         sqlite3_close(db);
//         return;
//     } 
//     rc = sqlite3_step(pStmt);

//     int bytes = 0;
//     if (rc == SQLITE_ROW) {
//         bytes = sqlite3_column_bytes(pStmt, 0);
//     }

//     const void *blob_data = sqlite3_column_blob(pStmt, 0);
//     if (blob_data == NULL) {    
//         rc = sqlite3_finalize(pStmt);
//         sqlite3_close(db);
//         return;
//     }
    
//     // Reading blob image
//     unsigned char *write_data = malloc(bytes + 1);
//     memcpy(write_data, blob_data, bytes);
//     write_data[bytes] = '\0';

//     // Encoding readed image
//     unsigned int out_size = b64e_size(bytes) + 1;
//     unsigned char *out_b64 = malloc((sizeof(char) * out_size));
//     b64_encode(write_data, bytes, out_b64);
//     free(write_data);

//     // Len of encoded image
//     int len_encoded = strlen((char *)out_b64);
    
//     // Sendin to client 
//     send(utils->user->client_fd, &len_encoded, sizeof(int), 0);
//     send_to_client(&utils->user->client_fd, out_b64, len_encoded);
    
//     free(out_b64);

//     sqlite3_finalize(pStmt);   
//     sqlite3_close(db);
// }
