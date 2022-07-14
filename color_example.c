#include <log.h>

int main(void)
{
    log_set_color();
    log_set_level(LOG_DEBUG);
    log_trace("colored trace log !");
    log_debug("colored debug log !");
    log_force_color(false);
    log_info("forced uncolored info log !");
    log_set_color();
    log_warn("colored warn log !");
    log_force_color(false);
    log_error("forced uncolored error log !");
    log_force_color(true);
    log_fatal("forced colored fatal log !");
    return 0;
}
