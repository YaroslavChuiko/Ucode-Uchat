#include "../inc/utils.h"

char* get_response_str(t_response_code error_code) {

    size_t arr_size = sizeof(response_objs) / sizeof(response_objs[0]);
    for (size_t i = 0; i < arr_size; ++i) {

        if (response_objs[i].code == error_code) {
            return response_objs[i].message;
        }
    
    }
    return NULL;

}
