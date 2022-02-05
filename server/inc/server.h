#ifndef SERVER_HEADER
#define SERVER_HEADER

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __MACH__
#include "../../libraries/openssl/openssl/ssl.h"
#include "../../libraries/openssl/openssl/err.h"
#else
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

#include "../../libraries/libmx/inc/libmx.h"
#include "../../utils/inc/utils.h"
#include "../../libraries/cjson/inc/cJSON.h"
#include "../../libraries/sqlite/inc/sqlite3.h"
#include "types.h"

// SERVER UTILS

void* thread_handler(void* arg);
void daemon_init();
void handle_arg_errors(char** argv);
void send_response_to(SSL* ssl, const char* response);
void send_server_response(SSL* ssl, t_response_code code, t_request_type req_type);\
void client_cleanup(t_server_utils* utils, bool is_client_exit);
int server_socket_init(struct sockaddr* serv_address, socklen_t address_size);
void new_client_create(SSL* ssl, int client_socket);
void handle_error(const char* error);

// REQUEST HANDLERS

t_request_type handle_request_for(const char* req_args, t_server_utils* utils);
char* get_new_message_json(t_msg* msg_to_send);
char* get_json_response_for(t_response_code error_code, t_request_type req_type);
t_request_type get_request_type(cJSON* json);
void handle_usr_login(const cJSON* user_info, t_server_utils* utils);
void handle_usr_signup(const cJSON* user_info, t_server_utils* utils);
void handle_create_chat(const cJSON* chat_info, t_server_utils* utils);
void handle_join_chat(const cJSON* chat_info, t_server_utils* utils);
void handle_get_chats(const cJSON* chat_info, t_server_utils* utils);
void handle_get_chat_msgs(const cJSON* chat_info, t_server_utils* utils);
void handle_search_chats(const cJSON* chat_info, t_server_utils* utils);
void handle_get_msg(const cJSON* msg_info, t_server_utils* utils);
void handle_last_msg_id(const cJSON* chat_info, t_server_utils* utils);
void handle_send_message(const cJSON* message_info, t_server_utils* utils);
void handle_delete_chat(const cJSON* chat_info, t_server_utils* utils);
void handle_delete_message(const cJSON* message_info, t_server_utils* utils);
void handle_edit_message(const cJSON* message_info, t_server_utils* utils);
void handle_edit_chat(const cJSON* chat_info, t_server_utils* utils);
void handle_edit_username(const cJSON* user_info, t_server_utils* utils);
void handle_edit_password(const cJSON* pass_info, t_server_utils* utils);
void handle_delete_account(const cJSON* chat_info, t_server_utils* utils);
void handle_leave_chat(const cJSON* chat_info, t_server_utils* utils);
t_request_type handle_usr_logout(const cJSON* logout_info, t_server_utils* utils);

void handle_set_default_user_image(char *path, int id);
void handle_update_user_image(const cJSON* data, t_server_utils* utils);
void handle_get_user_image(const cJSON* data, t_server_utils* utils);
// SQL

int database_init();
sqlite3* open_database();
int db_execute_query(const char* query);
sqlite3_stmt* db_execute_stmt_for(const char* query, sqlite3* db);

t_response_code db_insert_chat(const char* chat_name, int date, int avatar_color);
bool db_chat_exists(int chat_id);
int db_get_chats_total(int user_id);
bool db_has_chat_perms(int user_id, int chat_id, t_member_type perms);
bool db_user_exists(const char* username);
char* db_get_username_by_id(int user_id);
t_chat* db_get_chat_by_id(int user_id, int chat_id);
int db_insert_member(const char* chat_name, t_member_type member_type, t_server_utils* utils);
t_user* db_get_user_by_id(int user_id, t_server_utils* utils);
bool db_is_chat_member(int user_id, int chat_id);
int db_get_chat_id_by_name(const char* chat_name);
cJSON* get_chat_json(sqlite3_stmt* stmt, bool is_for_search);
cJSON* get_msg_json(sqlite3_stmt* stmt);
int db_get_id_by_username(const char* username);

// LIST UTILS

t_user *mx_create_user(int id, int client_fd, SSL* ssl);
void mx_user_push_back(t_user** list, int user_id, int client_fd, SSL* ssl);
void mx_user_pop_index(t_user **list, int index);
t_user* mx_get_user_by_id(t_user* list, int user_id);
void mx_clear_user_list(t_user **list);
void mx_clear_user(t_user** p);
int mx_get_user_id(int user_db_id);

// An array of function pointers for request handlers
static const t_req_handler request_handlers[] = {
    handle_usr_signup,
    handle_usr_login,
    handle_create_chat,
    handle_join_chat,
    handle_send_message,
    handle_leave_chat,
    handle_delete_chat,
    handle_delete_message,
    handle_edit_message,
    handle_update_user_image,
    handle_get_user_image,
    handle_get_chats,
    handle_get_chat_msgs,
    handle_get_msg,
    handle_last_msg_id,
    handle_search_chats,
    handle_edit_chat,
    handle_edit_username,
    handle_edit_password,
    handle_delete_account,
    NULL
};

// SSL
void ssl_init(SSL_CTX **ctx);

#endif
