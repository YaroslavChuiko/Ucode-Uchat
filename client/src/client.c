#include "../inc/client.h"

t_client_utils* utils;
GtkWidget *main_window;

// void* handle_requests(void* arg);
int main(int argc, char **argv) {

	(void)argc;
	handle_arg_errors(argv);

	int server_socket = 0;
	// pthread_t th_write;
	// pthread_t th_read;
	
	SSL_CTX *ctx = NULL; 
	SSL *ssl = NULL;

	connect_to_server(atoi(argv[1]), &server_socket, &ctx, &ssl);
	client_init(server_socket, ssl, ctx);

	GtkWidget* window;
	
    gtk_init(&argc, &argv);

	main_window = create_new_window("login", 500, 0, false);

	// CSS
	GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "client/data/styles/styles.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
	//

	GtkWidget* main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(main_area, "main_area");
	gtk_container_add(GTK_CONTAINER(main_window), main_area);

	build_login_menu(&main_area);
    gtk_widget_show_all(main_window);

    gtk_main();

	// pthread_create(&th_read, NULL, handle_server_updates, utils);
	// utils->th_reader = th_read;
	// pthread_create(&th_write, NULL, handle_requests, NULL);
// 
	// pthread_join(th_write, NULL);

	return EXIT_SUCCESS;

}

// void* handle_requests(void* arg) {

// 	// t_client_utils* utils = (t_client_utils*)arg;
// 	while (1) {

// 		char client_request[32];
// 		char user_name[32];
// 		char user_password[32];
// 		char *user_info = NULL;

// 		printf("Enter your request ('signup', 'login', 'create chat', 'message'): ");
// 		fgets(client_request, 32, stdin);

// 		if (!mx_strncmp(client_request, "signup", 6)) {
			
// 			printf("Please enter your name: ");
// 			fgets(user_name, 32, stdin);
// 			char* user = mx_strndup(user_name, mx_get_char_index(user_name, '\n'));

// 			printf("Enter your password: ");
// 			fgets(user_password, 32, stdin);
			
// 			handle_signup_request(user, user_password);

// 		} else if (!mx_strncmp(client_request, "login", 5)) {

// 			printf("Please enter your name: ");
// 			fgets(user_name, 32, stdin);
// 			char* user = mx_strndup(user_name, mx_get_char_index(user_name, '\n'));

// 			printf("Enter your password: ");
// 			fgets(user_password, 32, stdin);

// 			handle_login_request(user, user_password);

// 		} else if (!mx_strncmp(client_request, "create chat", 11)) {

// 			char chat_name[32];
// 			printf("Please enter chat's name: ");
// 			fgets(chat_name, 32, stdin);
// 			char* chat = mx_strndup(chat_name, mx_get_char_index(chat_name, '\n'));

// 			handle_create_chat_request(chat);

// 		} else if (!mx_strncmp(client_request, "message", 7)) {

// 			char message[1024];
// 			printf("Enter your message: ");
// 			fgets(message, 1024, stdin);

// 			handle_send_msg_request(message);

// 		} else if (!mx_strncmp(client_request, "join chat", 9)) {

// 			char chat_name[100];
// 			printf("Enter a chat to join: ");
// 			fgets(chat_name, 100, stdin);
// 			char* chat = mx_strndup(chat_name, mx_get_char_index(chat_name, '\n'));

// 			handle_join_chat_request(chat);

// 		} else if (!strncmp(client_request, "get chats", 9)) {

// 			handle_get_chats_request();

// 		} else if (strncmp(client_request, "exit", 4) == 0) {
// 			handle_logout_request();
// 			pthread_detach(pthread_self());
// 			client_cleanup(&utils);
// 			pthread_exit((void*)EXIT_SUCCESS);
// 		}

// 		mx_strdel(&user_info);
// 	}
// 	return NULL;

// }
