#include "../inc/utils.h"

void logger(const char* info, t_info_type type) {

    FILE* fd = fopen(LOGFILE_NAME, "a+");
    fprintf(fd, "%s: ", type == ERROR_LOG ? "ERROR" : "INFO");
    fprintf(fd, "%s\n", info);
    fclose(fd);

}
