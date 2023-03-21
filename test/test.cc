#include <iostream>
#include "../aki/log.h"
#include "../aki/util.h"

int main(int argc, char** argv) {
    aki::Logger::ptr logger(new aki::Logger);
    logger -> addAppender(aki::LogAppender::ptr(new aki::StdoutLogAppender));
    aki::LogEvent::ptr event(new aki::LogEvent(logger, aki::LogLevel::DEBUG, __FILE__, __LINE__, 0, aki::GetThreadId(), aki::GetFiberId(), time(0)));
    event->getSS() << "hello sylar DEBUG";
    logger -> log(aki::LogLevel::DEBUG, event);
    
    
    AKI_LOG_INFO(logger) << "test macro";
    AKI_LOG_ERROR(logger) << "test macro error";
    
    return 0;
}