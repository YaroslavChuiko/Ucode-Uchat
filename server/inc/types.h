#ifndef TYPES_H
#define TYPES_H

// Type for the chat saved from the database
typedef struct s_chat {
    int id;
    char* name;
    struct s_chat* next;
}              t_chat;

// Type for the user saved from the database
typedef struct s_user {
    int client_fd;
    int user_id;
    char* name;
    char* password;
    t_chat* chats;
    struct s_user* next;
}              t_user;

// Type for the user saved from the database
typedef struct s_msg {
    int chat_id;
    char* text;
    t_user* sender;
}              t_msg;

typedef struct s_server_utils {
    int client_socket;
    t_user* user;
}              t_server_utils;

typedef struct s_state {
    pthread_mutex_t lock;
    t_user* logged_users;
}              t_server_state;

typedef void (*t_req_handler)(const cJSON* user_info, t_server_utils* utils);

#endif
