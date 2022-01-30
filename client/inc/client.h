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

#ifdef __MACH__
#include "../../libraries/openssl/openssl/ssl.h"
#include "../../libraries/openssl/openssl/err.h"
#else
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

#include "../../libraries/cjson/inc/cJSON.h"
#include "../../libraries/libmx/inc/libmx.h"
#include "../../utils/inc/utils.h"

#include "const.h"
#include "types.h"

unsigned long get_current_time();
char* mx_get_string_time(unsigned long seconds);

//GUI UTILS
void on_crossing (GtkWidget *widget, GdkEventCrossing *event);
void add_class(GtkWidget *widget, char *class_name);
void remove_class(GtkWidget *widget, char *class_name);
void set_field_error_style(GtkWidget *field);
void set_field_success_style(GtkWidget *field);
void set_notify_error_style( GtkWidget *notify_label, char *message);
void set_notify_success_style( GtkWidget *notify_label, char *message);
GtkWidget *get_widget_by_name(GtkWidget *container, char *name);
GtkWidget *get_widget_by_name_r(GtkWidget *container, char *name);

//BUILD WINDOWS
// void destroy(GtkWidget* widget, gpointer data);
GtkWidget* create_new_window(char *title, int width, int height, bool resizable);
GtkWidget *create_popup_window(int width, int height);
void build_authorizatioin_window();
void build_chat_window();

//AUTH
void build_login_menu();
void build_signup_menu();
void build_chat_screen();

//AUTH EVENTS
void signup_button_click(GtkWidget *widget, gpointer data);
void login_button_click(GtkWidget *widget, gpointer data);
void switch_to_signup_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void switch_to_login_menu(GtkWidget *widget, GdkEventButton *event, gpointer main_area);
void focus_out_username_field(GtkWidget *widget, gpointer data);
void focus_out_password_field(GtkWidget *widget, gpointer data);
void focus_out_repassword_field(GtkWidget *widget, gpointer data);
bool is_empty_field(GtkWidget *field, GtkWidget *notify_label);

//CHATLIST
void add_chatlist_item(int id, char *chat_name);
void build_chatlist_message(char *message);

//CHATLIST EVENTS
void clear_container(GtkWidget *container);
void update_chatlist();
void set_chatlist_item_active(GtkWidget *widget);
void set_current_chat(GtkWidget *chatlist_item);
void chatlist_item_on_click(GtkWidget *widget, gpointer data);
void activate_chat(GtkWidget *chatlist_item);

void build_start_messaging_label();////////////////////////////////
// void build_delete_chat_btn();/////////////?????????????????????????????

//SEARCH CHAT
void search_field_change_event(GtkWidget *widget, gpointer data);
void clear_search_field(GtkWidget *widget, gpointer entry_field);
void search_field_enter_pressed(GtkWidget *widget, gpointer data);

//DELETE CHAT EVENTS
void delete_chat_btn_click(GtkWidget *widget, gpointer data);

//CREATE CHAT MENU
void build_create_chat_menu(GtkWidget *main_area);

//CREATE CHAT MENU EVENTS
void popup_create_chat_menu(GtkWidget *widget, GdkEventButton *event, gpointer chat_screen);
void create_chat_btn_click(GtkWidget *widget, gpointer data);

//JOIN CHAT
void join_chat_event(GtkWidget *widget, GdkEventButton *event, gpointer data);
void add_join_chat_item(int id, char *chat_name);

//LOG OUT
void logout_btn_click(GtkWidget *widget, gpointer data);

//VALIDATION
bool validate_name_field(GtkWidget *username_field, GtkWidget *username_notify_label);
bool validate_password_field(GtkWidget *password_field, GtkWidget *password_notify_label);
bool validate_repassword_field(GtkWidget *password_field, GtkWidget *repassword_field, GtkWidget *repassword_notify_label);

//HANDLE RESPONSE CODE
void handle_login_response_code(int error_code, GtkWidget *login_notify_label);
void handle_signup_response_code(int error_code, GtkWidget *signup_notify_label);
void handle_create_chat_response_code(int error_code, GtkWidget* entry_field, GtkWidget *create_chat_notify_label);
void handle_join_chat_response_code(int error_code, char *chat_name);

t_response_code handle_join_chat_request(const char* chat_name);
t_response_code handle_signup_request(const char* user_name, const char* user_password);
t_response_code handle_login_request(const char* user_name, const char* user_password);
t_response_code handle_create_chat_request(const char* chat_name);
t_response_code handle_send_msg_request(const char* message_str);
t_response_code handle_get_chats_request();
t_response_code handle_get_chat_msgs_request(int chat_id);
void handle_get_msg_request(int chat_id, int message_id);
t_msg* handle_get_msg_response();
t_chat* handle_search_chats_request(const char* search_str);
int handle_new_msg_count_request(int chat_id);
void handle_logout_request(bool is_client_exit);
void* handle_server_updates(void* arg);
int handle_delete_chat_request(const char* chat_name);
void handle_delete_msg_request(int message_id);
t_msg* get_msg_from_json(cJSON* json);
void handle_edit_msg_request(int message_id, const char* new_msg_text);

t_response_code handle_get_chats_response(t_chat** chat_list, const char* response_str, bool is_search);
t_response_code handle_server_response(const char* response_str);
int send_to_server(SSL *ssl, const char* request_str);
char* send_and_recv_from_server(SSL *ssl, const char* json_str);
char* recv_from_server(SSL* ssl);
t_response_code get_response_code(cJSON* json);
t_request_type get_request_type(cJSON* json);
void update_last_chat_msg(t_chat* chat_to_update, t_msg* new_msg);

void client_init(int server_fd, SSL *ssl, SSL_CTX* ctx);
void client_cleanup(bool is_client_exit);
void connect_to_server(int port, int* server_fd, SSL_CTX **ctx, SSL **ssl);
void handle_arg_errors(char** argv);

void init_ssl(SSL_CTX **ctx);
void connect_ssl(SSL **ssl, int* server_fd, SSL_CTX **ctx);
void client_log(const char* info, t_info_type type);
char* get_log_name();

void build_rightbar_chat();
void delete_message(GtkWidget *widget, GdkEventButton *event, t_msg *message);
void edit_button_click(GtkWidget *widget, t_msg *message);
void edit_message(GtkWidget *widget, GdkEventButton *event, t_msg *message);
void add_message(t_msg *message);
void update_chat_field();
void scroll_to_end(GtkWidget *widget, gpointer data);
void send_button_click(GtkWidget *widget, gpointer new_message_field);

#endif

