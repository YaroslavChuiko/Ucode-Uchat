#include "../inc/client.h"

unsigned long get_current_time() {

    signed long dt = 0;
    GDateTime *gtime = g_date_time_new_now_local();

    dt = g_date_time_to_unix(gtime);
    dt *= 1000000;
    dt += g_date_time_get_microsecond(gtime);
    dt /= 1000000;
    return dt;

}

char* mx_get_string_time(unsigned long seconds) {
    
    GDateTime *dt = g_date_time_new_from_unix_utc(seconds);
    GDateTime *new = g_date_time_to_local(dt);

    return (char*)g_date_time_format(new, "%d.%m.%Y %H:%M");

}
