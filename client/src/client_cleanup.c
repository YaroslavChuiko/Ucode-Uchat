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

void chat_cleanup(t_chat** chat) {

    if (!chat || !(*chat)) {
        return;
    }
	mx_strdel(&(*chat)->name);
	free(*chat);
	*chat = NULL;

}

void client_cleanup() {

	user_cleanup(&utils->current_user);
	chat_cleanup(&utils->current_chat);
	pthread_mutex_destroy(&utils->lock);
	
	SSL_free(utils->ssl);
	SSL_CTX_free(utils->ctx);
	
	free(utils);
	utils = NULL;

}
