#include "../inc/libmx.h"

char* mx_str_tolower(char* str) {

    char* new_str = mx_strdup(str);
    for (int i = 0; new_str[i] != '\0'; ++i) {

        new_str[i] = mx_tolower(new_str[i]);

    }
    return new_str;

}
