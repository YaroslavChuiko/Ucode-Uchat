#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <regex.h>

#include "db_types.h"

extern int errno;

#define LOGFILE_NAME "server_utils/info_log.txt"
#define SENT_DATA_LEN 1024

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
    R_NAME_FORMAT_INVALID,

    R_MSG_USR_NOENT,
}            t_response_code;

// Enum for the client request type
typedef enum e_request_type {
    REQ_USR_SIGNUP,
    REQ_USR_LOGIN,
    REQ_CREATE_CHAT,
    REQ_JOIN_CHAT,
    REQ_SEND_MESSAGE,
    REQ_USR_LOGOUT,
    REQ_GET_CHAT,
    
    REQ_NEW_MESSAGE,
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
    { R_DB_FAILURE, "A json error occurred when handling the request" },
    { R_INVALID_INPUT, "The input was invalid" },
    { R_USR_EXISTS, "The user with this name already exists" },
    { R_USR_NOENT, "There's no user by that name" },
    { R_INVALID_PASS, "The entered password is incorrect" },
    { R_CHAT_EXISTS, "The chat with this name already exists" },
    { R_CHAT_NOENT, "The chat with this name doesn't exist" },
    { R_IS_CHAT_MEMBER, "You're already a member of this chat" },
    { R_ISNT_CHAT_MEMBER, "You're not a member of this chat" },
    { R_NAME_FORMAT_INVALID, "The name should contain only letters and digits" },
    { R_MSG_USR_NOENT, "Couldn't find this message's sender" },
};

void logger(const char* info, t_info_type info_type);
char* get_response_str(t_response_code error_code);
bool is_user_name_format_valid(const char* name);


// DATABASE LISTS

t_chat *mx_create_chat(int id, const char* name, int permissions);
void mx_chat_push_back(t_chat** list, int id, const char* name, int permissions);
void mx_clear_chat_list(t_chat **list);

#endif
