#include <iostream>
#include "../aki/log.h"

int main(int argc, char** argv) {
    aki::Logger::ptr logger(new aki::Logger);
    logger -> addAppender(aki::LogAppender::ptr(new aki::StdoutLogAppender));
    aki::LogEvent::ptr event(new aki::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));
    logger -> log(aki::LogLevel::DEBUG, event);
    return 0;
}