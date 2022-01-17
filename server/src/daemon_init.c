#include "../inc/server.h"

void daemon_init() {

    pid_t pid, sid;
    
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);
    if ((sid = setsid()) < 0) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }
    // close(STDIN_FILENO);
    // close(STDOUT_FILENO);
    // close(STDERR_FILENO);
    signal(SIGTERM, SIG_DFL);

}
