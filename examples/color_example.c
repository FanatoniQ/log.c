#include "log.h"

int main(void)
{
    log_set_color();
    log_set_level(LOG_TRACE);
    log_trace("colored trace log !");
    log_debug("colored debug log !");
    log_info("colored info log !");
    log_warn("colored warn log !");
    log_error("colored error log !");
    log_fatal("colored fatal log !");
    return 0;
}
