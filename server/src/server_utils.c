#include "../inc/server.h"

// Check if command line arguments are valid
void handle_arg_errors(char** argv) {

	if (argv[1] == NULL) {
		mx_printerr("usage: ./uchat_server [port]\n");
	} 

}
