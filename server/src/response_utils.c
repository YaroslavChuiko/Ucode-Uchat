#include "../inc/server.h"

// Get a string-formatted error response from a created json object
char* get_json_response_for(t_response_code error_code, t_request_type req_type) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "error_code", error_code);
    cJSON_AddNumberToObject(json, "type", req_type);
    char* response_info = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return response_info;

}

// Send an error response to the client 
void send_server_response(SSL* ssl, t_response_code code, t_request_type req_type) {

    char* response = get_json_response_for(code, req_type);
    send_response_to(ssl, response);
    free(response);

}

// Send a string-formatted response to the client
void send_response_to(SSL* ssl, const char* response) {

    int response_len = mx_strlen(response);
    char* len_str = mx_itoa(response_len);
    // SSL_write(ssl, len_str, mx_strlen(len_str));
    SSL_write(ssl, response, response_len);
    mx_strdel(&len_str);

}
