#include "../inc/server.h"
#include <sys/select.h>

// Read client data (a request to be handled)
char* read_client_data(SSL *ssl) {

    char buffer[SENT_DATA_LEN];
    int n_bytes = 0;
    if ((n_bytes = SSL_read(ssl, buffer, SENT_DATA_LEN)) <= 0) {
        
        if (n_bytes == 0)
            return NULL;
        
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            sleep(1);
            return NULL;
        }
        logger(strerror(errno), ERROR_LOG);
        return NULL;
    
    }
    buffer[n_bytes] = '\0';
    return mx_strdup(buffer);

}

void* thread_handler(void* arg) {

    t_server_utils *server_utils = malloc(sizeof(*server_utils));
    server_utils->client_socket = ((t_server_utils *)arg)->client_socket;
    server_utils->ssl = ((t_server_utils *)arg)->ssl;
    server_utils->user = NULL;
    while (1) {

        char* request_str = NULL;
        if (!(request_str = read_client_data(server_utils->ssl)))
            continue;

        t_request_type req_type = -1;
        if ((req_type = handle_request_for(request_str, server_utils) == REQ_USR_LOGOUT)) {
            mx_strdel(&request_str);
            break;
        }
        mx_strdel(&request_str);

    }
    client_cleanup(server_utils);    
    pthread_detach(pthread_self());
    return NULL;

}
