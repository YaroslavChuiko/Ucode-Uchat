#include "../../inc/server.h"

char* get_chat_json_string(t_chat* chat) {

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat->id);
    cJSON_AddStringToObject(json, "chat_name", chat->name);
    cJSON_AddNumberToObject(json, "chat_permissions", chat->permissions);

    cJSON_AddNumberToObject(json, "type", REQ_GET_CHAT);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    char* json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return json_str;

}

void handle_get_chat(const cJSON* chat_info, t_server_utils* utils) {

    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");
    if (!cJSON_IsString(chat_name))    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_CHAT);
        return;
    }

    int chat_id = db_get_chat_id_by_name(chat_name->valuestring);
    if (chat_id == -1) {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_GET_CHAT);
        return;
    }

    if (!db_is_chat_member(utils->user->user_id, chat_id)) {
        send_server_response(utils->ssl, R_ISNT_CHAT_MEMBER, REQ_GET_CHAT);
        return;
    }

    t_chat* chat = NULL;
    if (!(chat = db_get_chat_by_id(utils->user->user_id, chat_id))) {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_GET_CHAT);
        return;
    }
    char* json_str = get_chat_json_string(chat);
    send_response_to(utils->ssl, json_str);
    free(json_str);
    
}
