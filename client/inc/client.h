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

#define IP_ADDRESS      "127.0.0.1" // remove later

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define LEFT_BAR_W 360
#define LEFT_BAR_H 720

struct {
    GtkWidget *username_field;
    GtkWidget *username_notify_label;
    GtkWidget *password_field;
    GtkWidget *password_notify_label;
    GtkWidget *repassword_field;
    GtkWidget *repassword_notify_label;
    GtkWidget *result_notify_label;
}   t_auth_fields;

struct {
    GtkWidget *login_event;
    GtkWidget *signup_event;
}   t_auth_menu;

struct {
    // GtkWidget *chat_screen;
    GtkWidget *popup_menu;
    // GtkWidget *left_bar;
    GtkWidget *chat_list;
    // GtkWidget *chat;
}   t_chat_screen;

typedef struct s_user {
    int user_id;
    char* name;
    char* password;
}              t_user;

typedef struct s_chat {
    int chat_id;
    char* name;
}              t_chat;

typedef struct s_client_utils {
    int server_fd;
    SSL* ssl;
    SSL_CTX* ctx;
    // pthread_t th_reader;
    pthread_mutex_t lock;
    t_user* current_user;
    t_chat* current_chat;
}              t_client_utils;

extern t_client_utils *utils;

void build_login_menu(GtkWidget **main_area);
void build_signup_menu(GtkWidget **main_area);
void build_chat_screen(GtkWidget **main_area);

void on_crossing (GtkWidget *widget, GdkEventCrossing *event);
void add_class(GtkWidget *widget, char *class_name);
void remove_class(GtkWidget *widget, char *class_name);

void signup_button_click(GtkWidget *widget, gpointer data);
void switch_to_login_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void login_button_click(GtkWidget *widget, gpointer data);
void switch_to_signup_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void focus_out_username_field(GtkWidget *widget, gpointer data);
void focus_out_password_field(GtkWidget *widget, gpointer data);
void focus_out_repassword_field(GtkWidget *widget, gpointer data);

bool is_empty_username(char *user_name);
bool is_empty_password(char *user_password);

bool check_valid_username(char *username);
bool check_valid_password(char *user_password);
bool check_valid_repassword(char *user_password, char *user_repassword);

void handle_login_error_code(int error_code);
void handle_signup_error_code(int error_code);
void handle_create_chat_error_code(int error_code, GtkWidget* entry_field);

void handle_join_chat_request(const char* chat_name);
int handle_signup_request(const char* user_name, const char* user_password);
int handle_login_request(const char* user_name, const char* user_password);
void handle_logout_request();
int handle_create_chat_request(const char* chat_name);
void handle_send_msg_request(const char* message_str);
t_response_code handle_new_message(cJSON* json);
void* handle_server_updates(void* arg);

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

