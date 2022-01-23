#include "../inc/utils.h"

static bool is_pattern_matched_for(const char* str, const char* pattern) {

    regex_t regex;
    int result = 0;
    
    if ((result = regcomp(&regex, pattern, 0))) {
        logger("Could not compile regex", ERROR_LOG);
        return false;
    }
    
    result = regexec(&regex, str, 0, NULL, 0);
    
    regfree(&regex);
    return result != REG_NOMATCH;

}

bool is_user_name_format_valid(const char* user_name) {

    return is_pattern_matched_for(user_name, "^[a-zA-Z0-9_-]*$");

}
