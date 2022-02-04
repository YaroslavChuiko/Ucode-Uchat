#include "../inc/client.h"

t_client_utils* utils;
GtkWidget *main_window;

int main(int argc, char **argv) {

	(void)argc;
	handle_arg_errors(argv);
	srand(time(NULL));

	int server_socket = 0;
	pthread_t th_write;
	pthread_t th_read;
	
	SSL_CTX *ctx = NULL; 
	SSL *ssl = NULL;

	connect_to_server(atoi(argv[1]), &server_socket, &ctx, &ssl);
	client_init(server_socket, ssl, ctx);

    gtk_init(&argc, &argv);

	// CSS
	GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "client/data/styles/main.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
	//

	build_authorizatioin_window();

	pthread_create(&th_read, NULL, handle_server_updates, utils);
	utils->th_reader = th_read;

    gtk_main();

	return EXIT_SUCCESS;

}
