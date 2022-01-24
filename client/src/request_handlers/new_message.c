#include "../../inc/client.h"

// Get a new text message if the read data is an update
static t_msg* get_new_message(cJSON* json) {

	if (cJSON_IsNull(json))
		return NULL;

	const cJSON *user_id = cJSON_GetObjectItem(json, "sender_id");
    const cJSON *chat_id = cJSON_GetObjectItem(json, "chat_id");
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(json, "sender_name");
    const cJSON *message = cJSON_GetObjectItemCaseSensitive(json, "text");
    const cJSON *date = cJSON_GetObjectItemCaseSensitive(json, "date");
	if (!cJSON_IsString(message)) {
		logger("Error receiving a new message", ERROR_LOG);
		return NULL;
	}
	t_msg* new_msg = mx_create_msg(user_id->valueint, user_name->valuestring, chat_id->valueint, 
                                    message->valuestring, date->valuestring);
	return new_msg;

}

// Handle a response to a new message from another client
t_response_code handle_new_message(cJSON* json) {

    t_msg* new_msg = NULL;
    if (!(new_msg = get_new_message(json)))
        return R_JSON_FAILURE;

    char msg[200];
    sprintf(msg, "new message for %s, %s -- %s\n", new_msg->sender_name, new_msg->text, new_msg->date_str);
    logger(msg, INFO_LOG);
	// mx_strdel(&message_text);
	mx_clear_msg_list(&new_msg);
    
    return R_SUCCESS;

}
