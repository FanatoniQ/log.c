#include <log.h>

int main(void)
{
    log_set_level(LOG_DEBUG);
    log_trace("trace log !");
    log_debug("debug log !");
    log_info("info log !");
    log_warn("warn log !");
    log_error("error log !");
    log_fatal("fatal log !");
    return 0;
}
