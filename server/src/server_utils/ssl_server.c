#include "../../inc/server.h"

void ssl_sertificate(SSL_CTX *ctx, const char* cert, const char* key) {

	if (SSL_CTX_use_certificate_file(ctx, cert, SSL_FILETYPE_PEM) <= 0)
	{
		logger(strerror(errno), ERROR_LOG);
		exit(EXIT_FAILURE);
	}

	if (SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM) <= 0)
	{
		logger(strerror(errno), ERROR_LOG);
		exit(EXIT_FAILURE);
	}

	if (!SSL_CTX_check_private_key(ctx))
	{
		logger(strerror(errno), ERROR_LOG);
		exit(EXIT_FAILURE);
	}

}

void ssl_init(SSL_CTX **ctx) {
	const char cert[] = "server/cert.crt";
	const char key[] = "server/key.key";

	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	*ctx = SSL_CTX_new(TLS_server_method());
	
	if (!*ctx) {
		logger(strerror(errno), ERROR_LOG);
		exit(EXIT_FAILURE);
	}
	
	ssl_sertificate(*ctx, cert, key);

}
