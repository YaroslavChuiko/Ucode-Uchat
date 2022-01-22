#include "../inc/client.h"

void user_cleanup(t_user** user) {

    if (!user || !(*user)) {
        return;
    }
	mx_strdel(&(*user)->name);
	mx_strdel(&(*user)->password);
	free(*user);
	*user = NULL;

}

void client_cleanup() {

	user_cleanup(&utils->current_user);
	mx_clear_chat(&utils->current_chat);
	mx_clear_chat_list(&utils->chatlist);
	pthread_mutex_destroy(&utils->lock);
	
	SSL_free(utils->ssl);
	SSL_CTX_free(utils->ctx);
	
	free(utils);
	utils = NULL;

}
