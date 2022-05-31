#include "../inc/server.h"

int server_socket_init(struct sockaddr* serv_address, socklen_t address_size) {

    int server_socket = 0;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (bind(server_socket, serv_address, address_size) == -1) {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) == -1) {
        handle_error(strerror(errno));
        // exit(EXIT_FAILURE);
    }
    return server_socket;

}

void new_client_create(SSL* ssl, int client_socket) {

    pthread_t thread;

    if (SSL_accept(ssl) == -1) {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    int flags = fcntl(client_socket,F_GETFL,0);
    if (flags == -1)
        logger(strerror(errno), ERROR_LOG);
    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);
    fcntl(client_socket, F_SETFD, O_NONBLOCK);

    t_server_utils* utils = malloc(sizeof(*utils));
    utils->client_socket = client_socket;
    utils->ssl = ssl;
    utils->user = NULL;

    pthread_create(&thread, NULL, thread_handler, (void *)utils);

}

// Check if command line arguments are valid
void handle_arg_errors(char** argv) {

	if (argv[1] == NULL) {
		mx_printerr("usage: ./uchat_server [port]\n");
        exit(EXIT_FAILURE);
	} 

}

// Make current process a daemon
void daemon_init() {

    pid_t pid, sid;
    
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        printf("The process id is: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    umask(0);
    if ((sid = setsid()) < 0) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }
    signal(SIGTERM, SIG_DFL);

}

void handle_error(const char* error) {

	char* err_str = mx_strjoin(error, "\n");
    mx_printerr(err_str);
    logger(err_str, ERROR_LOG);
	mx_strdel(&err_str);

}
