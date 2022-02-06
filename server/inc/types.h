#ifndef SERVER_TYPES_H
#define SERVER_TYPES_H

// Type for the user saved from the database
typedef struct s_user {
    int client_fd;
    SSL* ssl;
    int user_id;
    char* name;
    char* password;
    t_avatar_color avatar_color;
    struct s_user* next;
}              t_user;

// Type for major utilities, used by the server
typedef struct s_server_utils {
    int client_socket;
    SSL *ssl;
    t_user* user;
}              t_server_utils;

typedef void (*t_req_handler)(const cJSON* user_info, t_server_utils* utils);

#endif
