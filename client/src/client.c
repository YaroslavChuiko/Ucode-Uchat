#include "../inc/client.h"

t_client_utils* utils;
GtkWidget *main_window;

void* handle_requests(void* arg);
int main(int argc, char **argv) {

	(void)argc;
	handle_arg_errors(argv);

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
    gtk_css_provider_load_from_path(styles, "client/data/styles/styles.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
	//

	build_authorizatioin_window();

	// pthread_create(&th_read, NULL, handle_server_updates, utils);
	// utils->th_reader = th_read;
	// pthread_join(th_read, NULL);

    gtk_main();
	// pthread_create(&th_write, NULL, handle_requests, NULL);

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

// 		} else if (!mx_strncmp(client_request, "delete chat", 11)) {

// 			char chat_name[100];
// 			printf("Enter a name of chat to delete: ");
// 			fgets(chat_name, 100, stdin);
// 			char* chat = mx_strndup(chat_name, mx_get_char_index(chat_name, '\n'));

// 			handle_delete_chat_request(chat);

// 		} else if (!mx_strncmp(client_request, "message", 7)) {

// 			char message[1024];
// 			printf("Enter your message: ");
// 			fgets(message, 1024, stdin);

// 			handle_send_msg_request(message);

// 		} else if (!mx_strncmp(client_request, "delete message", 14)) {

// 			char id_char[1024];
// 			printf("Enter id of message to delete: ");
// 			fgets(id_char, 1024, stdin);
// 			int id = atoi(id_char);
// 			handle_delete_msg_request(id);

// 		} else if (!mx_strncmp(client_request, "join chat", 9)) {

// 			char chat_name[100];
// 			printf("Enter a chat to join: ");
// 			fgets(chat_name, 100, stdin);
// 			char* chat = mx_strndup(chat_name, mx_get_char_index(chat_name, '\n'));

// 			handle_join_chat_request(chat);

// 		} else if (!strncmp(client_request, "get chats", 9)) {

// 			handle_get_chats_request();

// 		} else if (!strncmp(client_request, "search chat", 9)) {

// 			char chat_name[100];
// 			printf("Enter a chat to search: ");
// 			fgets(chat_name, 100, stdin);
// 			char* chat = mx_strndup(chat_name, mx_get_char_index(chat_name, '\n'));

// 			handle_search_chats_request(chat);

// 		} else if (!strncmp(client_request, "set chat", 8)) {

// 			char chat_id[100];
// 			printf("Enter a chat id: ");
// 			fgets(chat_id, 100, stdin);
// 			pthread_mutex_lock(&utils->lock);
// 			if (utils->current_chat && utils->current_chat->id == -1)
// 				mx_clear_chat(&utils->current_chat);
// 			utils->current_chat = mx_get_chat_by_id(utils->chatlist, atoi(chat_id));
// 			pthread_mutex_unlock(&utils->lock);

// 		} else if (!strncmp(client_request, "get msg", 7)) {

// 			char chat_id[100];
// 			char msg_id[100];
// 			printf("Enter a chat id: ");
// 			fgets(chat_id, 100, stdin);
// 			printf("Enter a msg id: ");
// 			fgets(msg_id, 100, stdin);

// 			handle_get_msg_request(atoi(chat_id), atoi(msg_id));
// 			handle_get_msg_response();

// 		} else if (!strncmp(client_request, "new msg count", 13)) {

// 			char chat_id[100];
// 			printf("Enter a chat id: ");
// 			fgets(chat_id, 100, stdin);

// 			handle_new_msg_count_request(atoi(chat_id), true);

// 		} else if (strncmp(client_request, "exit", 4) == 0) {
// 			handle_logout_request();
// 			pthread_cancel(utils->th_reader);
// 			client_cleanup(&utils);
// 			pthread_exit(NULL);
// 		}

// 		mx_strdel(&user_info);
// 	}
// 	return NULL;

// }
