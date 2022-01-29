#include "../../inc/client.h"

static int handle_new_message(t_chat* curr_chat, int message_id) {

	handle_get_msg_request(curr_chat->id, message_id);
	t_msg* new_msg = NULL;

	if (!(new_msg = handle_get_msg_response())) {
		// t_msg* msg_to_remove = mx_get_msg_by_id(curr_chat->messages, message_id);
		// if (msg_to_remove->sender_id != utils->current_user->user_id) {
		// 	mx_msg_pop_id(&curr_chat->messages, message_id);
		// }
		return 1;
	}

	pthread_mutex_lock(&utils->lock);
	if (utils->current_chat && curr_chat->id == utils->current_chat->id) {

		// if the current chat is the one where we got new messages
		// generate a new widget for the created `new_msg` here
		char str[200];
		sprintf(str, "You're reading an incoming message from %s", curr_chat->name);
		client_log(str, INFO_LOG);

		mx_msg_push_back(&curr_chat->messages, new_msg);

	} else {
		// if we got messages from a different chat (the one not being selected)
		char str[200];
		sprintf(str, "You have an incoming message from %s", curr_chat->name);
		client_log(str, INFO_LOG);
	}

	if (curr_chat->last_new_msg)
		mx_clear_msg(&curr_chat->last_new_msg);

	curr_chat->last_new_msg = mx_create_msg(new_msg->message_id, new_msg->sender_id, new_msg->sender_name, 
											new_msg->chat_id, new_msg->text, new_msg->date_str);

	pthread_mutex_unlock(&utils->lock);
	char str[200];
	sprintf(str, "This is a t_msg msg:\n\ttext: %s, chat_id: %d, sender_id: %d, sender_name: %s, date: %s\n", 
			new_msg->text, new_msg->chat_id, new_msg->sender_id, new_msg->sender_name, new_msg->date_str);
	client_log(str, INFO_LOG);
	g_usleep(10000);
	return 0;
	
}

//	Thread handler for checking and handling server updates
void* handle_server_updates(void* arg) {
	
	(void)arg;
    while (1) {

		if (utils && utils->is_suspended)
			continue;
		
		if (!utils)
			break;

		pthread_mutex_lock(&utils->lock);
		t_chat* curr_chat = utils->chatlist;
		pthread_mutex_unlock(&utils->lock);
		while (curr_chat) {

			pthread_mutex_lock(&utils->lock);
			bool is_current_chat = utils->current_chat && curr_chat->id == utils->current_chat->id;
			pthread_mutex_unlock(&utils->lock);

			int new_msg_count = handle_new_msg_count_request(curr_chat->id, is_current_chat);
			if (new_msg_count <= 0) {
				curr_chat = curr_chat->next;
				continue;
			}
			
			int last_msg_id = mx_get_last_msg_id(curr_chat, is_current_chat, utils->current_user->user_id);
			for (int i = 1; i <= new_msg_count; ++i) {
				
				if (handle_new_message(curr_chat, last_msg_id + i) != 0)
					continue;

			}
			g_usleep(0.5 * 1000000);
			curr_chat = curr_chat->next;

		}
		g_usleep(0.5 * 1000000);

	}
	return NULL;

}
