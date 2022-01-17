#include "../../inc/server.h"

static bool is_user_in_chat(t_chat* curr_chat, int chat_id) {

    while (curr_chat) {
            
        if (curr_chat->id == chat_id) {
            return true;
        }
        curr_chat = curr_chat->next;

    }
    return false;

}

void send_response_to_all(t_msg* msg_to_send) {

    t_user* curr_user = global_state.logged_users;
    while (curr_user) {

        // if (msg_to_send->sender->user_id == curr_user->user_id)
            // continue;
        
        if (!is_user_in_chat(curr_user->chats, msg_to_send->chat_id)) {
            curr_user = curr_user->next;
            continue;
        }

        char* msg_json = get_new_message_json(msg_to_send);
        send_response_to(curr_user->client_fd, msg_json);
        free(msg_json);

        curr_user = curr_user->next;
        
    }

}
