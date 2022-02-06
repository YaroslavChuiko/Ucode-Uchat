#include "../inc/client.h"

t_client_utils* utils;
GtkWidget *main_window;

int main(int argc, char **argv) {

	(void)argc;
	handle_arg_errors(argv);
	srand(time(NULL));

	int server_socket = 0;
	SSL_CTX *ctx = NULL; 
	SSL *ssl = NULL;

	connect_to_server(argv[1], atoi(argv[2]), &server_socket, &ctx, &ssl);
	client_init(server_socket, ssl, ctx);

    gtk_init(&argc, &argv);

	load_css();
	build_authorization_window();

    // gtk_window_set_icon_from_file(GTK_WINDOW(main_window), "client/data/img/logo.png", NULL);
    // gtk_window_set_icon_name(GTK_WINDOW(main_window), "UChat");

	pthread_create(&utils->th_reader, NULL, handle_server_updates, utils);

    gtk_main();

	return EXIT_SUCCESS;

}
