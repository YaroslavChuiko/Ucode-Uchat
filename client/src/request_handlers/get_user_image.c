#include "../../inc/client.h"

void recv_image_from_server(int *socket, unsigned char **buffer, size_t length) {
    unsigned char *ptr = *buffer;
    while (length > 0) {
        int i = recv(*socket, ptr, length, 0);
        ptr += i;
        length -= i;
    }
}

static char* get_file_path_for(int user_id) {

    char* id_str = mx_itoa(user_id);
    char* file_name = mx_strnew(mx_strlen(AVATAR_PATH) + mx_strlen(id_str) + 9);
    mx_strcat(file_name, AVATAR_PATH);
    mx_strcat(file_name, id_str);
    mx_strcat(file_name, "_user.png");
    return file_name;

}

t_response_code handle_get_user_image(int user_id, char** avatar_path) {

    utils->is_suspended = true;
    // Send request for receiving user avatar
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_GET_USER_IMAGE);
    cJSON_AddNumberToObject(json, "user_id", user_id); 
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    send_to_server(utils->ssl, json_str);
    free(json_str);

    // Creating temp file
    FILE *fp;
    char* file_path = get_file_path_for(user_id);
    if ((fp = fopen(file_path, "wb")) == NULL) {
        printf("Cannot open image file\n");
        mx_strdel(&file_path);
        return R_FILE_ERROR;
    }

    // Reciving len of encoded image
    int len_encoded = 0;
    usleep(500000);
    if(recv(utils->server_fd, &len_encoded, sizeof(int), 0) == 0) {
        printf("Error while receiving length\n");
        mx_strdel(&file_path);
        return R_FILE_ERROR;
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
        mx_strdel(&file_path);
        return R_FILE_ERROR;
    }
    int r;
    if ((r = fclose(fp)) == EOF) {
        printf("Cannot close file handler\n");
        mx_strdel(&file_path);
        return R_FILE_ERROR;
    }

    free(decoded);
    
    if (*avatar_path) {
        mx_strdel(avatar_path);
    }
    *avatar_path = mx_strdup(file_path);
    mx_strdel(&file_path);
    utils->is_suspended = false;
    return R_SUCCESS;

}
