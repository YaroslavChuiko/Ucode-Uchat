#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <regex.h>

#include "base64.h"
#include "db_types.h"
#include "const.h"
#include "../../libraries/libmx/inc/libmx.h"

extern int errno;

// Enum for the type of info being logged
typedef enum e_info_type {
    INFO_LOG,
    ERROR_LOG
}            t_info_type;

// Enum for the code of the server response to the client
typedef enum e_response_code {
    R_SUCCESS,
    R_DB_FAILURE,
    R_JSON_FAILURE,
    R_INVALID_INPUT,
    
    R_USR_EXISTS,
    R_USR_NOENT,
    R_INVALID_PASS,
    R_CHAT_EXISTS,
    R_CHAT_NOENT,
    R_IS_CHAT_MEMBER,
    R_ISNT_CHAT_MEMBER,
    R_NO_CHAT_PERMS,
    R_CHATS_TOTAL_REACHED,
    R_NAME_FORMAT_INVALID,
    R_NAME_LEN_INVALID,
    R_PASS_LEN_INVALID,
    R_MSG_LEN_INVALID,

    R_MSG_USR_NOENT,
}            t_response_code;

// Enum for the client request type
typedef enum e_request_type {
    REQ_USR_SIGNUP,
    REQ_USR_LOGIN,
    REQ_CREATE_CHAT,
    REQ_JOIN_CHAT,
    REQ_SEND_MESSAGE,
    REQ_LEAVE_CHAT,
    REQ_DELETE_CHAT,
    REQ_DELETE_MESSAGE,
    REQ_EDIT_MESSAGE,

    REQ_UPDATE_USER_IMAGE,
    REQ_GET_USER_IMAGE,

    REQ_GET_CHATS,
    REQ_GET_CHAT_MSGS,
    REQ_GET_MSG,
    REQ_LAST_MSG_ID,
    REQ_SEARCH_CHATS,
    REQ_EDIT_CHAT,
    REQ_EDIT_USERNAME,
    REQ_EDIT_PASSWORD,
    REQ_DELETE_ACCOUNT,
    
    REQ_USR_LOGOUT,
    REQ_CLIENT_EXIT,
}            t_request_type;

typedef struct s_response {
    t_response_code code;
    char* message;
}              t_response;

// Const array of response codes + their error messages 
static const t_response response_objs[] = {
    { R_SUCCESS, "Request handled successfully" },
    { R_DB_FAILURE, "A database error occurred when handling the request" },
    { R_JSON_FAILURE, "A json error occurred when handling the request" },
    { R_INVALID_INPUT, "The input was invalid" },
    { R_USR_EXISTS, "The user with this name already exists" },
    { R_USR_NOENT, "There's no user by that name" },
    { R_INVALID_PASS, "The entered password is incorrect" },
    { R_CHAT_EXISTS, "The chat with this name already exists" },
    { R_CHAT_NOENT, "The chat with this name doesn't exist" },
    { R_IS_CHAT_MEMBER, "You're already a member of this chat" },
    { R_ISNT_CHAT_MEMBER, "You're not a member of this chat" },
    { R_NO_CHAT_PERMS, "You don't have the permissions for this action" },
    { R_CHATS_TOTAL_REACHED, "You can't be a member of more than 15 chats" },
    { R_NAME_FORMAT_INVALID, "The name should contain only letters and digits" },
    { R_NAME_LEN_INVALID, "The name's length should be in a (4, 16) range" },
    { R_PASS_LEN_INVALID, "The password's length should be in a (8, 30) range" },
    { R_MSG_LEN_INVALID, "The message's length can't be greater than 1024 symbols" },
    { R_MSG_USR_NOENT, "Couldn't find this message's sender" },
};

void logger(const char* info, t_info_type info_type);
char* get_response_str(t_response_code error_code);
bool is_user_name_format_valid(const char* name);
bool is_strlen_valid(const char* str, int min_len, int max_len);


// DATABASE LISTS

t_chat *mx_create_chat(int id, const char* name, int permissions, int chat_color);
void mx_chat_push_back(t_chat** list, int id, const char* name, int permissions, int chat_color);
void mx_clear_chat_list(t_chat **list);
void mx_clear_chat(t_chat** p);
t_chat* mx_get_chat_by_id(t_chat* list, int chat_id);
void mx_chat_pop_id(t_chat **list, int chat_id);
void mx_chat_pop_index(t_chat **list, int index);
int mx_chat_list_size(t_chat* list);

void mx_print_chat_list(t_chat* chat); // remove

t_msg* mx_create_msg(int msg_id, int user_id, const char* user_name, int chat_id, const char* text, const char* date_str);
void mx_msg_dfl_push_back(t_msg** list, int msg_id, int user_id, const char* user_name, int chat_id, const char* text, const char* date_str);
void mx_msg_push_back(t_msg** list, t_msg* new_node);
void mx_clear_msg_list(t_msg **list);
void mx_msg_pop_index(t_msg **list, int index);
void mx_msg_pop_id(t_msg **list, int msg_id);
int mx_get_msg_idx_by_id(t_msg* list, int id);
void mx_clear_msg_list(t_msg **list);
int mx_msg_list_size(t_msg* list);
int mx_get_last_msg_id(t_chat* chat);
t_chat* mx_get_chat_by_name(t_chat* list, const char* name);
t_msg* mx_get_msg_by_id(t_msg* list, int id);
void mx_clear_msg(t_msg** p);
t_msg* mx_get_last_msg_node(t_msg* list);
void mx_print_msg(t_msg* msg); // remove

#endif
