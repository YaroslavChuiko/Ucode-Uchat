#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <gtk/gtk.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "../../libraries/cjson/inc/cJSON.h"
#include "../../libraries/libmx/inc/libmx.h"
#include "../../utils/inc/utils.h"

#include "const.h"
#include "types.h"

GtkWidget* create_new_window(char *title, int width, int height, bool resizable);

void build_login_menu(GtkWidget **main_area);
void build_signup_menu(GtkWidget **main_area);
void build_chat_screen(GtkWidget **main_area);

void destroy(GtkWidget* widget, gpointer data);
void on_crossing (GtkWidget *widget, GdkEventCrossing *event);
void add_class(GtkWidget *widget, char *class_name);
void remove_class(GtkWidget *widget, char *class_name);
void set_field_error_style(GtkWidget *field);
void set_field_success_style(GtkWidget *field);
void set_notify_error_style( GtkWidget *notify_label, char *message);
void set_notify_success_style( GtkWidget *notify_label, char *message);
GtkWidget *get_widget_by_name(GtkWidget *container, char *name);
GtkWidget *get_widget_by_name_r(GtkWidget *container, char *name);

void signup_button_click(GtkWidget *widget, gpointer data);
void switch_to_login_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void login_button_click(GtkWidget *widget, gpointer data);
void switch_to_signup_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void focus_out_username_field(GtkWidget *widget, gpointer data);
void focus_out_password_field(GtkWidget *widget, gpointer data);
void focus_out_repassword_field(GtkWidget *widget, gpointer data);

bool is_empty_field(GtkWidget *field, GtkWidget *notify_label);
// bool is_empty_password(char *user_password);

bool validate_name_field(GtkWidget *username_field, GtkWidget *username_notify_label);
bool validate_password_field(GtkWidget *password_field, GtkWidget *password_notify_label);
bool validate_repassword_field(GtkWidget *password_field, GtkWidget *repassword_field, GtkWidget *repassword_notify_label);

void handle_login_error_code(int error_code, GtkWidget *login_notify_label);
void handle_signup_error_code(int error_code, GtkWidget *signup_notify_label);
void handle_create_chat_error_code(int error_code, GtkWidget* entry_field, GtkWidget *create_chat_notify_label);

void popup_create_chat_menu(GtkWidget *widget, GdkEventButton *event, gpointer chat_screen);

t_response_code handle_join_chat_request(const char* chat_name);
t_response_code handle_signup_request(const char* user_name, const char* user_password);
t_response_code handle_login_request(const char* user_name, const char* user_password);
t_response_code handle_create_chat_request(const char* chat_name);
t_response_code handle_send_msg_request(const char* message_str);
t_response_code handle_new_message(cJSON* json);
t_response_code handle_get_chats_request();
t_response_code handle_get_chat_msgs_request(int chat_id);
void handle_logout_request();
void handle_client_exit();
void* handle_server_updates(void* arg);
int handle_delete_chat_request(const char* chat_name);
void handle_delete_msg_request(int message_id);

bool is_request_for_update(t_request_type type);
t_request_type get_request_type(cJSON* json);
t_response_code handle_server_response(const char* response_str);
int send_to_server(SSL *ssl, const char* request_str);
t_response_code get_response_code(cJSON* json);
char* send_and_recv_from_server(SSL *ssl, const char* json_str);

void client_init(int server_fd, SSL *ssl, SSL_CTX* ctx);
void client_cleanup();
void connect_to_server(int port, int* server_fd, SSL_CTX **ctx, SSL **ssl);
void handle_arg_errors(char** argv);

void init_ssl(SSL_CTX **ctx);
void connect_ssl(SSL **ssl, int* server_fd, SSL_CTX **ctx);

#endif
