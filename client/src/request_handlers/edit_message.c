#include "../../inc/client.h"

void handle_edit_msg_request(int message_id, const char* new_msg_text) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_MESSAGE);
    cJSON_AddNumberToObject(json, "id", message_id);
    cJSON_AddStringToObject(json, "text", new_msg_text);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);

    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char* response = send_and_recv_from_server(utils->ssl, json_str);
    int error_code = handle_server_response(response);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(json_str);
    free(response);

}
