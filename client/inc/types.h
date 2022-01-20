#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

#include <gtk/gtk.h>

extern GtkWidget *main_window;

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
    GtkWidget *login_menu;
    GtkWidget *signup_menu;
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

#endif
