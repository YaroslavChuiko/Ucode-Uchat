#include "../inc/server.h"

int main(int argc, char *argv[]) {

    (void)argc;
    handle_arg_errors(argv);

    struct sockaddr_in serv_address, client_address;
    int client_socket;
    socklen_t address_size = sizeof(struct sockaddr_in);

    daemon_init();

	SSL_CTX *ctx = NULL;
	SSL *ssl = NULL;
	ssl_init(&ctx);

    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = INADDR_ANY;
    serv_address.sin_port = htons(atoi(argv[1]));

    int server_socket = server_socket_init((struct sockaddr *)&serv_address, address_size);

	while (1) {

        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_size)) != -1) {
        
        	ssl = SSL_new(ctx);
			SSL_set_fd(ssl, client_socket);
			
			new_client_create(ssl, client_socket);

        } else {
            
            handle_error(strerror(errno));
        
        }
	}
	
	return EXIT_FAILURE;

}
