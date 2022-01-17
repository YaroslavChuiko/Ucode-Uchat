#include "../../inc/client.h"

// Get a new text message if the read data is an update
static char* get_new_message(cJSON* json) {

	if (cJSON_IsNull(json))
		return NULL;

	cJSON* msg_json = cJSON_GetObjectItemCaseSensitive(json, "text");
	if (!cJSON_IsString(msg_json)) {
		logger("Error receiving a new message", ERROR_LOG);
		return NULL;
	}
	return mx_strdup(msg_json->valuestring);

}

// Handle a response to a new message from another client
t_response_code handle_new_message(cJSON* json) {

    char* message_text = NULL;
    if (!(message_text = get_new_message(json)))
        return R_JSON_FAILURE;

    char msg[200];
    sprintf(msg, "new message for %d, %s -- %s\n", utils->current_user->user_id, utils->current_user->name, message_text);
    logger(msg, INFO_LOG);
	mx_strdel(&message_text);
    
    return R_SUCCESS;

}
