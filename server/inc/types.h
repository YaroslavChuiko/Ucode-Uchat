#ifndef TYPES_H
#define TYPES_H

// Type for the user saved from the database
typedef struct s_user {
    int client_fd;
    SSL* ssl;
    int user_id;
    char* name;
    char* password;
    t_chat* chats;
    struct s_user* next;
}              t_user;

typedef struct s_server_utils {
    int client_socket;
    SSL *ssl;
    t_user* user;
}              t_server_utils;

typedef struct s_state {
    pthread_mutex_t lock;
    t_user* logged_users;
}              t_server_state;

typedef void (*t_req_handler)(const cJSON* user_info, t_server_utils* utils);

#endif
