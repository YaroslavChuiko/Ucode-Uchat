#include "../inc/client.h"

void user_cleanup(t_user** user) {

    if (!user || !(*user)) {
        return;
    }
	mx_strdel(&(*user)->name);
	mx_strdel(&(*user)->password);
	mx_strdel(&(*user)->avatar_path);
	free(*user);
	*user = NULL;

}

void client_cleanup(bool is_client_exit) {

	pthread_mutex_lock(&utils->lock);
	user_cleanup(&utils->current_user);
	mx_clear_chat_list(&utils->chatlist);
	mx_strdel(&utils->log_name);
	pthread_mutex_unlock(&utils->lock);

	if (is_client_exit) {
		pthread_mutex_destroy(&utils->lock);
		SSL_free(utils->ssl);
		SSL_CTX_free(utils->ctx);
		free(utils);
		utils = NULL;
	}	
	
}
