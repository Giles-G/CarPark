#ifndef LOG_H
#define LOG_H

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "BlockQueue.hpp"

using namespace std;

class Log {
   public:
    static Log* get_instance() {
        static Log instance;
        return &instance;
    }

    static void* flush_log_thread(void* args) {
        Log::get_instance()->async_write_log();
        return nullptr;
    }
    
    /**
     * @brief The optional parameters are log file, log buffer size, maximum number of lines and longest log bar queue
     * 
     * @return true 
     * @return false 
     */
    bool init(const char* file_name,
              int close_log,
              int log_buf_size = 8192,
              int split_lines = 5000000,
              int max_queue_size = 0);

    void write_log(int level, const char* format, ...);

    void flush(void);

   private:
    Log();
    virtual ~Log();
    void* async_write_log() {
        string single_log;
        // Remove a log string from the blocked queue and write to a file
        while (m_log_queue->pop(single_log)) {
            m_mutex.lock();
            fputs(single_log.c_str(), m_fp);
            m_mutex.unlock();
        }
        return nullptr;
    }

   private:
    char dir_name[128];  // path name
    char log_name[128];  // log file name
    int m_split_lines;   // Maximum number of log lines
    int m_log_buf_size;  // log buffer size
    long long m_count;   // log line count record
    int m_today;         // Because it is classified by day, record the current time as that day
    FILE* m_fp;          // Open log file pointer
    char* m_buf;
    block_queue<string>* m_log_queue;  // blocking queue
    bool m_is_async;                   // Whether to synchronize the flag bit
    locker m_mutex;
    int m_close_log;     // close log
};

#define LOG_DEBUG(format, ...)                                    \
    if (0 == m_close_log) {                                       \
        Log::get_instance()->write_log(0, format, ##__VA_ARGS__); \
        Log::get_instance()->flush();                             \
    }
#define LOG_INFO(format, ...)                                     \
    if (0 == m_close_log) {                                       \
        Log::get_instance()->write_log(1, format, ##__VA_ARGS__); \
        Log::get_instance()->flush();                             \
    }
#define LOG_WARN(format, ...)                                     \
    if (0 == m_close_log) {                                       \
        Log::get_instance()->write_log(2, format, ##__VA_ARGS__); \
        Log::get_instance()->flush();                             \
    }
#define LOG_ERROR(format, ...)                                    \
    if (0 == m_close_log) {                                       \
        Log::get_instance()->write_log(3, format, ##__VA_ARGS__); \
        Log::get_instance()->flush();                             \
    }

#endif
