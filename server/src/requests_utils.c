#include "../inc/server.h"

// Get the type of the request from the read json object
t_request_type get_request_type(cJSON* json) {

    return cJSON_GetObjectItem(json, "type")->valueint;

}

// Call a handler for any valid client request
t_request_type handle_request_for(const char* request, t_server_utils* utils) {

    cJSON *json = cJSON_Parse(request);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            char error[200];
            sprintf(error, "Error before: %s\n", error_ptr);
            logger(error, ERROR_LOG);
        }
        return -1;
    }

    int type = get_request_type(json);
    char str[100];
    sprintf(str, "The type of the request is: %d\n", type);
    logger(str, INFO_LOG);
    
    if (type == REQ_CLIENT_EXIT) {
        cJSON_Delete(json);
        return type;
    }

    // call the request handler for the gotten type
    request_handlers[type](json, utils);
    
    cJSON_Delete(json);
    return type;

}
