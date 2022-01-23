#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

#include <gtk/gtk.h>

extern GtkWidget *main_window;

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

#endif
