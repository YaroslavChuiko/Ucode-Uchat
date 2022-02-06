#include "../../inc/client.h"

void send_image_to_server(int *socket, void *buffer, size_t length) {
    unsigned char *ptr = (unsigned char *)buffer;
    while (length > 0) {
        int i = send(*socket, ptr, length, 0);
        ptr += i;
        length -= i;
    }
}

t_response_code handle_update_user_image(char *path) {

    utils->is_suspended = true;

    // Send request for saving user avatar
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_UPDATE_USER_IMAGE);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id); 
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    send_to_server(utils->ssl, json_str);
    free(json_str);
    
    // Open image to read
    FILE *fp;
    if((fp = fopen(path, "rb")) == NULL) {
        handle_error("Cannot open file");
        return R_FILE_ERROR;
    }
    int r;
    
    // Get the length of the file data
    fseek(fp, 0, SEEK_END);
    if (ferror(fp)) {
        handle_error("fseek() failed");
        if ((r = fclose(fp)) == EOF) {
            handle_error("Cannot close file");         
        }
        return R_FILE_ERROR;
    }  
    
    long flen = ftell(fp);
    if (flen == -1) {
        handle_error("ftell() failed");
        if ((r = fclose(fp)) == EOF) {
            handle_error("Cannot close file");
        }
        return R_FILE_ERROR;
    }
    
    fseek(fp, 0, SEEK_SET);
    if (ferror(fp)) {
        handle_error("fseek() failed");
        r = fclose(fp);
        if (r == EOF) {
            handle_error("Cannot close file");
        }
        return R_FILE_ERROR;
    }

    // Read the data of the file which will be sent to server
    unsigned char *read_data = malloc((unsigned)flen + 1);
    fread(read_data, flen, 1, fp);
    if (ferror(fp)) {
        handle_error("fread() failed");
        if ((r = fclose(fp)) == EOF) {
            handle_error("Cannot close file");
        }
        return R_FILE_ERROR;
    }
    
    // Encode readed data
    unsigned int out_size = b64e_size(flen) + 1;
    unsigned char *out_b64 = malloc( (sizeof(char) * out_size) );
    mx_memset(out_b64, 0, out_size);
    b64_encode(read_data, flen, out_b64);
    
    free(read_data);

    int len_encoded = strlen((char *)out_b64);
    // handle_error("%d\n", len_encoded);
    // handle_error("%s\n", out_b64);
    // Send all to server
    send(utils->server_fd, &len_encoded, sizeof(int), 0);
    send_image_to_server(&utils->server_fd, out_b64, len_encoded);

    free(out_b64); 

    if ((r = fclose(fp)) == EOF) {
        handle_error("Cannot close file");
        return R_FILE_ERROR;
    }
    utils->is_suspended = false;
    return R_SUCCESS;

}
