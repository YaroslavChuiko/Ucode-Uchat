#include "../inc/client.h"

void init_ssl(SSL_CTX **ctx) {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    
    *ctx = SSL_CTX_new(SSLv23_client_method());
    if (*ctx == NULL) {
        logger(strerror(errno), ERROR_LOG);
		exit(EXIT_FAILURE);
    } 
}

void connect_ssl(SSL **ssl, int* server_fd, SSL_CTX **ctx) {
	*ssl = SSL_new(*ctx);
	SSL_set_mode(*ssl, SSL_MODE_ASYNC);
	SSL_set_fd(*ssl, *server_fd);

	if (SSL_connect(*ssl) == -1) {
		logger(strerror(errno), ERROR_LOG);
		exit(EXIT_FAILURE);
	}
}

