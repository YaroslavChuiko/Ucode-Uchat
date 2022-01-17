#include "../inc/server.h"
#include <sys/select.h>

// Read client data (a request to be handled)
char* read_client_data(int client_fd) {

    char buffer[SENT_DATA_LEN];
    int n_bytes = 0;
    if ((n_bytes = recv(client_fd, buffer, SENT_DATA_LEN, 0)) <= 0) {
        
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

    t_server_utils *temp_utils = malloc(sizeof(*temp_utils));
    temp_utils->client_socket = ((t_server_utils *)arg)->client_socket;
    temp_utils->user = NULL;

    while (1) {

        char* request_str = NULL;
        if (!(request_str = read_client_data(temp_utils->client_socket)))
            continue;

        if (strncmp(request_str, "exit", 4) == 0) {
            break;
        }

        handle_request_for(request_str, temp_utils);
        mx_strdel(&request_str);

    }
    close(temp_utils->client_socket);
    free(temp_utils);
    pthread_exit(EXIT_SUCCESS);

}
