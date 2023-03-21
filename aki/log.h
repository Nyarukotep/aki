#ifndef _AKI_LOG_H_
#define _AKI_LOG_H_

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

#define AKI_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        aki::LogEventWrap(aki::LogEvent::ptr(new aki::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, aki::GetThreadId(),\
                aki::GetFiberId(), time(0)))).getSS()

#define AKI_LOG_DEBUG(logger) AKI_LOG_LEVEL(logger, aki::LogLevel::DEBUG)
#define AKI_LOG_INFO(logger) AKI_LOG_LEVEL(logger, aki::LogLevel::INFO)
#define AKI_LOG_WARN(logger) AKI_LOG_LEVEL(logger, aki::LogLevel::WARN)
#define AKI_LOG_ERROR(logger) AKI_LOG_LEVEL(logger, aki::LogLevel::ERROR)
#define AKI_LOG_FATAL(logger) AKI_LOG_LEVEL(logger, aki::LogLevel::FATAL)



namespace aki {

    class Logger;

    class LogLevel {
        public:
            enum Level {
                UNKNOW = 0,
                DEBUG = 1,
                INFO = 2,
                WARN = 3,
                ERROR = 4,
                FATAL = 5
            };
            static const char* ToString(LogLevel::Level level);
    };

    class LogEvent {
        public:
            typedef std::shared_ptr<LogEvent> ptr;
            LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int32_t line, uint32_t elapse
                ,uint32_t thread_id, uint32_t fiber_id, uint64_t time);

            const char* getFile() const { return m_file;}
            int32_t getLine() const { return m_line;}
            uint32_t getElapse() const { return m_elapse;}
            uint32_t getThreadId() const { return m_threadId;}
            uint32_t getFiberId() const { return m_fiberId;}
            uint64_t getTime() const { return m_time;}
            std::string getContent() const { return m_ss.str();}
            std::shared_ptr<Logger> getLogger() const { return m_logger;}
            LogLevel::Level getLevel() const { return m_level;}
            std::stringstream& getSS() { return m_ss;}
        private:
            const char* m_file = nullptr;
            int32_t m_line = 0;
            uint32_t m_elapse = 0;
            uint32_t m_threadId = 0;
            uint32_t m_fiberId = 0;
            uint64_t m_time = 0;
            std::string m_threadName;
            std::stringstream m_ss;
            std::shared_ptr<Logger> m_logger;
            LogLevel::Level m_level;
    };

    class LogEventWrap {
        public:
            LogEventWrap(LogEvent::ptr e);
            ~LogEventWrap();
            std::stringstream& getSS();
        private:
            LogEvent::ptr m_event;
    };

    class LogFormatter {
        public:
            typedef std::shared_ptr<LogFormatter> ptr;
            LogFormatter(const std::string& pattern);
            std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
            
        public:
            class FormatItem {
                public:
                    typedef std::shared_ptr<FormatItem> ptr;
                    virtual ~FormatItem() {}
                    virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
                };
            void init();
        private:
            std::string m_pattern;
            std::vector<FormatItem::ptr> m_items;
        };

    class LogAppender {
        public:
            typedef std::shared_ptr<LogAppender> ptr;
            virtual ~LogAppender() {}
            virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
            void setFormatter(LogFormatter::ptr val) { m_formatter = val;}
            LogFormatter::ptr getFormatter() const { return m_formatter;}
            LogLevel::Level getLevel() const { return m_level;}
            void setLevel(LogLevel::Level val) { m_level = val;}
        protected:
            LogLevel::Level m_level = LogLevel::DEBUG;
            LogFormatter::ptr m_formatter;
    };


    class Logger : public std::enable_shared_from_this<Logger> {
        public:
            typedef std::shared_ptr<Logger> ptr;
            Logger(const std::string& name = "root");
            void log(LogLevel::Level level, LogEvent::ptr event);
            void debug(LogEvent::ptr event);
            void info(LogEvent::ptr event);
            void warn(LogEvent::ptr event);
            void error(LogEvent::ptr event);
            void fatal(LogEvent::ptr event);

            void addAppender(LogAppender::ptr appender);
            void delAppender(LogAppender::ptr appender);

            LogLevel::Level getLevel() const { return m_level;}
            void setLevel(LogLevel::Level val) { m_level = val;}
            const std::string& getName() const { return m_name;}

            void setFormatter(LogFormatter::ptr val);
            void setFormatter(const std::string& val);

            LogFormatter::ptr getFormatter();

        private:
            std::string m_name;
            LogLevel::Level m_level;
            std::list<LogAppender::ptr> m_appenders;
            LogFormatter::ptr m_formatter;
    };


class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

};

class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

}
#endif