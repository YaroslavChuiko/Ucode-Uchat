#include "../inc/client.h"

t_client_utils* utils;

void destroy(GtkWidget* widget, gpointer data)
{
	if (utils->current_user)
		handle_logout_request();
	client_cleanup();
    gtk_main_quit();
}

void add_class(GtkWidget *widget, char *class_name)
{
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_class(context, class_name);
}

void remove_class(GtkWidget *widget, char *class_name)
{
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_style_context_remove_class(context, class_name);
}

void on_crossing(GtkWidget *widget, GdkEventCrossing *event)
{
	GdkDisplay *display = gtk_widget_get_display(widget);
	GdkCursor *cursor;	

	switch (gdk_event_get_event_type((GdkEvent*)event))
	{
		case GDK_ENTER_NOTIFY:
			gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE); // it's for trigger :hover for this widget in CSS
			cursor = gdk_cursor_new_from_name (display, "hand1");
			break;

		case GDK_LEAVE_NOTIFY:
			gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT);
			cursor = gdk_cursor_new_from_name (display, "default");
			break;

		default:
			break;
	}

	gdk_window_set_cursor (gtk_widget_get_window(widget), cursor);

	// Release the reference on the cursor
	g_object_unref(cursor);
}

GtkWidget* create_new_window(char *title, int width, int height, bool resizable)
{
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); //GTK_WIN_POS_CENTER GTK_WIN_POS_CENTER_ON_PARENT
	gtk_window_set_resizable(GTK_WINDOW(window), resizable);
    g_signal_connect(window, "delete_event", G_CALLBACK(destroy), NULL); //delete_event

	return window;
}

int main(int argc, char **argv) {

	(void)argc;
	handle_arg_errors(argv);

	int server_socket = 0;
	// pthread_t th_write;
	pthread_t th_read;
	
	SSL_CTX *ctx = NULL; 
	SSL *ssl = NULL;

	connect_to_server(atoi(argv[1]), &server_socket, &ctx, &ssl);
	client_init(server_socket, ssl);

	GtkWidget* window;
	
    gtk_init(&argc, &argv);

	main_window = create_new_window("login", 500, 0, false);

	// CSS
	GtkCssProvider *styles = gtk_css_provider_new();
    gtk_css_provider_load_from_path(styles, "client/data/styles/styles.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER);
	//

	GtkWidget* main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(main_window), main_area);

	build_login_menu(&main_area);
    gtk_widget_show_all(main_window);

	// pthread_create(&th_read, NULL, handle_server_updates, utils);

    gtk_main();
	// utils->th_reader = th_read;
	// pthread_create(&th_write, NULL, handle_requests, utils);

	// pthread_join(th_write, NULL);

	return EXIT_SUCCESS;

}

// void* handle_requests(void* arg) {

// 	t_client_utils* utils = (t_client_utils*)arg;
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

// 			printf("Enter your password: ");
// 			fgets(user_password, 32, stdin);
			
// 			handle_signup_request(utils, user_name, user_password);

// 		} else if (!mx_strncmp(client_request, "login", 5)) {

// 			printf("Please enter your name: ");
// 			fgets(user_name, 32, stdin);

// 			printf("Enter your password: ");
// 			fgets(user_password, 32, stdin);

// 			handle_login_request(utils, user_name, user_password);

// 		} else if (!mx_strncmp(client_request, "create chat", 11)) {

// 			char chat_name[32];
// 			printf("Please enter chat's name: ");
// 			fgets(chat_name, 32, stdin);

// 			handle_create_chat_request(utils, chat_name);

// 		} else if (!mx_strncmp(client_request, "message", 7)) {

// 			char message[1024];
// 			printf("Enter your message: ");
// 			fgets(message, 1024, stdin);

// 			handle_send_msg_request(utils, message);

// 		} else if (!mx_strncmp(client_request, "join chat", 9)) {

// 			char chat_name[100];
// 			printf("Enter a chat to join: ");
// 			fgets(chat_name, 100, stdin);

// 			handle_join_chat_request(utils, chat_name);

// 		} else if (strncmp(client_request, "exit", 4) == 0) {
// 			send(utils->server_fd, client_request, 4, 0);
// 			pthread_detach(utils->th_reader);
// 			client_cleanup(&utils);
// 			pthread_exit((void*)EXIT_SUCCESS);
// 		}

// 		mx_strdel(&user_info);
// 	}
// 	return NULL;

// }
