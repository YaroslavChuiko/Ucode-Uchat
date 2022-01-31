#include "../../inc/client.h"

static int handle_new_message(t_chat* curr_chat, int message_id, int new_msg_count) {

	bool is_current = utils->current_chat && curr_chat->id == utils->current_chat->id;
	bool to_change_count = new_msg_count > curr_chat->new_msg_count;
	int last_new_msg_id = curr_chat->last_new_msg ? curr_chat->last_new_msg->message_id : 0;
	if (message_id <= last_new_msg_id && !is_current) {
			printf("msg id -- %d, last new msg id -- %d\n", message_id, last_new_msg_id);
		return 1;
	}

	handle_get_msg_request(curr_chat->id, message_id);
	t_msg* new_msg = NULL;

	if (!(new_msg = handle_get_msg_response())) {
		return 1;
	}

	if (is_current) {

		client_log("You're reading an incoming message", INFO_LOG);

		mx_msg_push_back(&curr_chat->messages, new_msg);
		if (mx_msg_list_size(curr_chat->messages) == 1) {
			update_chat_field();
		}
		else {
			add_message(new_msg);
		}
		if (curr_chat->new_msg_count >= 1)
			curr_chat->new_msg_count -= 1;

	} else if (to_change_count) {
		
		client_log("You have an incoming message", INFO_LOG);
		curr_chat->new_msg_count += 1;
		curr_chat->last_new_msg = new_msg;
	
	}
	
	update_chatlist_item_info(curr_chat);

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

			int new_msg_count = handle_new_msg_count_request(curr_chat->id);
			if (new_msg_count <= 0) {
				curr_chat = curr_chat ? curr_chat->next : NULL;
				continue;
			}
			
			int last_msg_id = mx_get_last_msg_id(curr_chat);
			int curr_new_msg_count = curr_chat->new_msg_count;
			printf("last new msg id -- %d, new msg count -- %d\n", last_msg_id, new_msg_count);
			for (int i = 1; i <= curr_new_msg_count + 1; ++i) {
				
				if (handle_new_message(curr_chat, last_msg_id + i, new_msg_count) != 0)
					continue;

			}
			g_usleep(0.5 * 1000000);
			curr_chat = curr_chat ? curr_chat->next : NULL;

		}
		g_usleep(0.5 * 1000000);

	}
	return NULL;

}
