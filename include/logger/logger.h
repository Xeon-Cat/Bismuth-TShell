#ifndef BISMUTH_LOGGER_H
#define BISMUTH_LOGGER_H

#include <stdio.h>
#include <stdarg.h>

// 日志级别枚举
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// 初始化/关闭日志系统
void log_init(const char *filename);
void log_close();

// 核心日志写入函数
void log_write(LogLevel level, const char *format, ...);

// 便捷宏
#define LOG_DEBUG(...)    log_write(LOG_DEBUG, __VA_ARGS__)
#define LOG_INFO(...)     log_write(LOG_INFO, __VA_ARGS__)
#define LOG_WARNING(...)  log_write(LOG_WARNING, __VA_ARGS__)
#define LOG_ERROR(...)    log_write(LOG_ERROR, __VA_ARGS__)


#endif //BISMUTH_LOGGER_H
