#include "../inc/client.h"

// Send a string-formatted client request to the server
int send_to_server(SSL *ssl, const char* request_str) {

    int req_len = mx_strlen(request_str);
    char* len_str = mx_itoa(req_len);
    // SSL_write(ssl, len_str, mx_strlen(len_str));
    unsigned long err = 0;
    while (SSL_write(ssl, request_str, req_len) == -1) {

        // int server_sock = 0;
        // SSL* ssl;
        // SSL_CTX* ctx;
        // connect_to_server(8080, &server_sock, &ctx, &ssl);
        // utils->ssl = ssl;
        // utils->ctx = ctx;

        if ((err = ERR_get_error())) {
            printf("error is: %s\nreason -- %s\n", ERR_error_string(err, NULL), ERR_reason_error_string(err));
        }
        mx_strdel(&len_str);
        return 1;
    }
    mx_strdel(&len_str);
    return 0;

}

// Get a server's response code from the read json object 
t_response_code get_response_code(cJSON* json) {

    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            char error[200];
            sprintf(error, "Error before: %s\n", error_ptr);
            logger(error, ERROR_LOG);
        }
        return R_JSON_FAILURE;
    } 

    return cJSON_GetObjectItemCaseSensitive(json, "error_code")->valueint;

}

t_request_type get_request_type(cJSON* json) {

    cJSON* type_json = cJSON_GetObjectItem(json, "type");
	if (cJSON_IsNull(type_json))
		return -1;

    return type_json->valueint;

}

// Handle a server response to a request 
t_response_code handle_server_response(const char* response_str) {

    if (response_str == NULL)
        return R_INVALID_INPUT;

    cJSON* json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    cJSON_Delete(json);
    return error_code;

}

char* get_server_response(SSL* ssl, int length) {

    char buffer[SENT_DATA_LEN] = "";
    int bytesRead = 0;
    while (bytesRead < length) {

        int bytes = SSL_read(ssl, &buffer[bytesRead], length - bytesRead);
        if (bytes <= 0) {

            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                continue;
            }
            logger(strerror(errno), ERROR_LOG);
            return NULL;

        } else if (bytes < length) {
            
            bytesRead += bytes;
        
        } else if (bytes == length) {
        
            bytesRead = bytes;
            break;
        
        }
    }
    buffer[bytesRead] = '\0';
    return mx_strdup(buffer);

} 

// Receive a response to a request from server
char* recv_from_server(SSL* ssl) {

    int n_bytes = 0;
    char buffer[SENT_DATA_LEN] = "";

    while ((n_bytes = SSL_read(ssl, buffer, SENT_DATA_LEN)) <= 0) {

        if (n_bytes == 0)
            return NULL;

        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            continue;
        }
        logger(strerror(errno), ERROR_LOG);
        return NULL;
    
    }
    buffer[n_bytes] = '\0';
    return mx_strdup(buffer);
    // return get_server_response(ssl, atoi(buffer));

}

// Send a request to the server and call the handler for the response
char* send_and_recv_from_server(SSL *ssl, const char* json_str) {

    if (send_to_server(ssl, json_str) != 0)
        return NULL;

    return recv_from_server(ssl);

}
