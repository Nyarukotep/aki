#include <iostream>
#include "../aki/log.h"
#include "../aki/util.h"

int main(int argc, char** argv) {
    aki::Logger::ptr logger(new aki::Logger);
    logger -> addAppender(aki::LogAppender::ptr(new aki::StdoutLogAppender));
    //aki::LogEvent::ptr event(new aki::LogEvent(logger, aki::LogLevel::DEBUG, __FILE__, __LINE__, 0, aki::GetThreadId(), aki::GetFiberId(), time(0)));
    //event->getSS() << "hello sylar DEBUG";
    
    aki::FileLogAppender::ptr file_appender(new aki::FileLogAppender("./log.txt"));
    logger -> addAppender(file_appender);
    aki::LogFormatter::ptr fmt(new aki::LogFormatter("%d%T%m%n"));
    file_appender -> setFormatter(fmt);

    


    
    //logger -> log(aki::LogLevel::DEBUG, event);
    
    
    AKI_LOG_INFO(logger) << "test macro";
    AKI_LOG_ERROR(logger) << "test macro error";
    AKI_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");
    
    return 0;
}