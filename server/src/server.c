#include "../inc/server.h"

t_server_state global_state;

int main(int argc, char *argv[]) {

	// (void)argc;
    struct sockaddr_in serv_address, client_address;
    t_server_utils utils;
    int server_socket, sock_client;
    socklen_t address_size = sizeof(struct sockaddr_in);
    pthread_t thread;

    global_state.logged_users = NULL;
    pthread_mutex_init(&global_state.lock, NULL); // don't forget to destroy after

    daemon_init();

	// initialize to init ssl, certificate and key
	SSL_CTX *ctx = NULL;
	SSL *ssl = NULL;
	ssl_init(&ctx); 

    // Setup listening on localhost and port 8080
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = INADDR_ANY;
    serv_address.sin_port = htons(8080);

    // Set the socket descriptor
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        exit(EXIT_FAILURE);
    }

    // Bind the sock_descriptor to the serv_address
    if (bind(server_socket, (struct sockaddr *)&serv_address, address_size) == -1) {
        exit(EXIT_FAILURE);
    }

    // Marks sock_descriptor as listening and accepting incoming connections
    listen(server_socket, 0);

    // Infinite loop that spawns new threads for incoming connections.
	while (1) {

        // Accept incoming connection and get file descriptor to use when thread is created
        if ((sock_client = accept(server_socket, (struct sockaddr *)&client_address, &address_size)) != -1) {
        
        	ssl = SSL_new(ctx);
			SSL_set_fd(ssl, sock_client);
			
			if (SSL_accept(ssl) == -1) {
				logger(strerror(errno), ERROR_LOG);
				exit(EXIT_FAILURE);
			}
            
            int flags = fcntl(sock_client,F_GETFL,0);
            if (flags == -1)
                logger(strerror(errno), ERROR_LOG);
            fcntl(sock_client, F_SETFL, flags | O_NONBLOCK);
            fcntl(sock_client, F_SETFD, O_NONBLOCK);

            utils.client_socket = sock_client;
            utils.ssl = ssl;

            pthread_create(&thread, NULL, thread_handler, (void *)&utils);

        } else {
            
            logger(strerror(errno), ERROR_LOG);
        
        }
	}
	
	return EXIT_FAILURE;

}

// SERVER ISSUES

// MISC ISSUES

// Handle escaping of characters for the strings before saving them to the database
