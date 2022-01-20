#include "../inc/client.h"

// Send a string-formatted client request to the server
int send_to_server(SSL *ssl, const char* request_str) {

    if (SSL_write(ssl, request_str, strlen(request_str)) == -1) {
        // logger(strerror(errno), ERROR_LOG);
        return 1;
    }
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

// Send a request to the server and call the handler for the response
char* send_and_recv_from_server(SSL *ssl, const char* json_str) {

    if (send_to_server(ssl, json_str) != 0)
        return NULL;

    char response[SENT_DATA_LEN];
    int n_bytes = 0;
    while ((n_bytes = SSL_read(ssl, response, SENT_DATA_LEN)) <= 0) {

        if (n_bytes == 0)
            return NULL;

        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            // logger("blocked from send_and_recv\n", ERROR_LOG);
            sleep(1);
            continue;
        }
        logger(strerror(errno), ERROR_LOG);
        return NULL;
    
    }
    response[n_bytes] = '\0';
    return mx_strdup(response);

}
