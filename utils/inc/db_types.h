#ifndef DB_TYPES_H
#define DB_TYPES_H

// Type for the message saved from the server
typedef struct s_msg {
    int message_id;
    int chat_id;
    int sender_id;
    char* sender_name;
    char* date_str;
    char* text;
    char* avatar_path;
    struct s_msg* next;
}              t_msg;

// Type for the chat saved from the database
typedef struct s_chat {
    int id;
    char* name;
    int permissions;
    t_msg* messages;
    t_msg* new_messages;
    t_msg* last_new_msg;
    int new_msg_count;
    struct s_chat* next;
}              t_chat;

// Type for the type of a chat member
typedef enum e_member_type {
    ADMIN_MEMBER,
    NORMAL_MEMBER,
}            t_member_type;

// Type for the color of the default avatar
    // change the names to colors later
typedef enum e_avatar_color {
    A_COLOR_FIRST,
    A_COLOR_SECOND,
    A_COLOR_THIRD,
    A_COLOR_FOURTH,
}            t_avatar_color;

#endif
