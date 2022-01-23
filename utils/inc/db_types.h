#ifndef DB_TYPES_H
#define DB_TYPES_H

// Type for the message saved from the server
typedef struct s_msg {
    int chat_id;
    int sender_id;
    char* sender_name;
    // int date;
    char* text;
    struct s_msg* next;
}              t_msg;

// Type for the chat saved from the database
typedef struct s_chat {
    int id;
    char* name;
    int permissions;
    t_msg* messages;
    struct s_chat* next;
}              t_chat;

// Type for the type of a chat member
typedef enum e_member_type {
    ADMIN_MEMBER,
    NORMAL_MEMBER,
}            t_member_type;

#endif
