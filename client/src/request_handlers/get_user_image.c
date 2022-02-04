#include "../../inc/client.h"

void recv_image_from_server(int *socket, unsigned char **buffer, size_t length) {
    unsigned char *ptr = *buffer;
    while (length > 0) {
        int i = recv(*socket, ptr, length, 0);
        ptr += i;
        length -= i;
    }
}

void handle_get_user_image() {

    // Send request for receiving user avatar
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_GET_USER_IMAGE);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id); 
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    send_to_server(utils->ssl, json_str);
    free(json_str);

    // Creating temp file
    FILE *fp;
    if ((fp = fopen("client/data/avatars/received_avatar.png", "wb")) == NULL){
        printf("Cannot open image file\n");
    }

    // Reciving len of encoded image
    int len_encoded = 0;
    usleep(2000000);
    if(recv(utils->server_fd, &len_encoded, sizeof(int), 0) == 0){
        printf("Error while receiving length\n");
    }
    
    // Reciving encoded image
    unsigned char *encoded = malloc((sizeof(char) * len_encoded));
    mx_memset(encoded, 0, len_encoded);
    recv_image_from_server(&utils->server_fd, &encoded, len_encoded);

    // Decoding image
    unsigned int flen = b64d_size(len_encoded);
    unsigned char *decoded = malloc( (sizeof(char) * flen) + 1);
    flen = b64_decode(encoded, len_encoded, decoded);        
    free(encoded);

    // Writing decoded image to created file
    fwrite(decoded, flen, 1, fp);
    if (ferror(fp)) {
        printf("fwrite() failed\n");
    }
    int r;
    if ((r = fclose(fp)) == EOF) {
        printf("Cannot close file handler\n");
    }

    free(decoded);

}