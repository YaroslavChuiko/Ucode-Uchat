#include "../../inc/client.h"

void set_messages_as_read_for(t_chat* chat) {

	if (!chat || !chat->new_messages)
		return;

	t_msg* new_msg = chat->new_messages;
	while (new_msg) {

		mx_msg_dfl_push_back(&chat->messages, 
							new_msg->message_id, new_msg->sender_id, new_msg->sender_name,
							new_msg->chat_id, new_msg->text, new_msg->date_str);

		if (chat->new_msg_count >= 1)
			chat->new_msg_count -= 1;

		if (mx_msg_list_size(chat->messages) == 1) {
			update_chat_field();
		} else {
			t_msg* msg_to_add = mx_get_last_msg_node(chat->messages);
			add_message(msg_to_add);
		}
		new_msg = new_msg->next;

	}
	mx_clear_msg_list(&chat->new_messages);

}

static int handle_new_message(t_chat* curr_chat, int message_id, bool is_current) {

	t_msg* curr_last_node = mx_get_last_msg_node(curr_chat->messages);
	int curr_last_msg_id = curr_last_node ? curr_last_node->message_id : 0;
	int last_new_msg_id = curr_chat->last_new_msg ? curr_chat->last_new_msg->message_id : 0;

	handle_get_msg_request(curr_chat->id, message_id);
	t_msg* new_msg = NULL;

	if (!(new_msg = handle_get_msg_response())) {
		
		return 1;
	}

	if (is_current && message_id > curr_last_msg_id) {

		client_log("You're reading an incoming message", INFO_LOG);
		if (!curr_chat->new_messages) {
			
			mx_msg_push_back(&curr_chat->messages, new_msg);
			curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->messages);
			
			if (mx_msg_list_size(curr_chat->messages) == 1)
				update_chat_field();
			else
				add_message(curr_chat->last_new_msg);

			if (curr_chat->new_msg_count >= 1)
				curr_chat->new_msg_count -= 1;

		} else {

			set_messages_as_read_for(curr_chat);
			curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->messages);

		}

	} else if (message_id > last_new_msg_id) {
		
		client_log("You have an incoming message", INFO_LOG);
		mx_msg_push_back(&curr_chat->new_messages, new_msg);
		curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->new_messages);
		curr_chat->new_msg_count += 1;
	
	}
	
	update_chatlist_item_info(curr_chat);

	char str[200];
	sprintf(str, "This is a t_msg msg:\n\ttext: %s, chat_id: %d, sender_id: %d, sender_name: %s, date: %s\n", 
			new_msg->text, new_msg->chat_id, new_msg->sender_id, new_msg->sender_name, new_msg->date_str);
	client_log(str, INFO_LOG);
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
			
			bool is_current = utils->current_chat && curr_chat->id == utils->current_chat->id;
			int last_msg_id = handle_last_msg_id_request(curr_chat->id);
			if (last_msg_id <= 0) {
				curr_chat = curr_chat ? curr_chat->next : NULL;
				continue;
			}
	
			int curr_last_msg_id = curr_chat->last_new_msg ? curr_chat->last_new_msg->message_id : 0;
			if (last_msg_id <= curr_last_msg_id && !is_current) {
				curr_chat = curr_chat ? curr_chat->next : NULL;
				continue;
			}
			
			handle_new_message(curr_chat, last_msg_id, is_current);
			
			curr_chat = curr_chat ? curr_chat->next : NULL;
			g_usleep(0.5 * 1000000);

		}
		g_usleep(0.5 * 1000000);

	}
	return NULL;

}
