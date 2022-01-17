#include "../../inc/client.h"

// Check whether the read data was actually an update or logout
bool is_request_for_update(t_request_type type) {

	return (type == REQ_USR_LOGIN || 
			type == REQ_USR_LOGOUT);

}

// Read server data (either a response to a request, or an update for this client)
char* read_server_data(int server_fd) {

	char buffer[SENT_DATA_LEN];
	int n_bytes = 0;
	if ((n_bytes = recv(server_fd, buffer, SENT_DATA_LEN, 0)) <= 0) {

		if (n_bytes == 0)
			return NULL;

		if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
			sleep(4);
			return NULL;
		}
		logger(strerror(errno), ERROR_LOG);
		return NULL;

	}
	buffer[n_bytes] = '\0';
	return mx_strdup(buffer);
	
}

/*	Thread handler for checking and handling server updates
	Note: the read server data could be a response to a request,
	in which case it's omitted in updater and is handled via handle_requests()   
*/
void* handle_server_updates(void* arg) {
	
    while (1) {

		char* update_str = NULL;
		if (!(update_str = read_server_data(utils->server_fd))) {
			logger("No data to read\n", ERROR_LOG);
			usleep(10000);
			continue;
		}
		// never getting here if sleeping more than other functions that also have to `recv`
		cJSON* json = cJSON_Parse(update_str);

		t_request_type req_type = get_request_type(json);
		printf("req_type here -- %d\n", req_type);
		if (req_type == -1 || !is_request_for_update(req_type)) {
			cJSON_Delete(json);
			continue;
		}

		if (req_type == REQ_USR_LOGOUT) {
			
			char str[100];
			sprintf(str, "Logging out for %d, %s\n", utils->current_user->user_id, utils->current_user->name);
			logger(str, INFO_LOG);
			pthread_exit(EXIT_SUCCESS);
		
		} else if (req_type == REQ_USR_LOGIN) {

			logger("Logged from server_updates -- ", INFO_LOG);

		}
		
		cJSON_Delete(json);
		mx_strdel(&update_str);

	}
	return NULL;

}
