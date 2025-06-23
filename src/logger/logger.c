#include "logger/logger.h"

#include <time.h>
#include <string.h>
#include <errno.h>

static FILE *log_fp = NULL;       // 日志文件指针
static const char *log_filename;  // 日志文件名

// 日志级别字符串映射
static const char* level_strings[] = {
        "DEBUG", "INFO", "WARNING", "ERROR"
};

// 初始化日志系统
void log_init(const char *filename) {
    log_filename = filename;
    log_fp = fopen(log_filename, "a");  // 追加模式
    if (!log_fp) {
        fprintf(stderr, "ERROR: Failed to open log file: %s\n", strerror(errno));
    }
}

// 关闭日志系统
void log_close() {
    if (log_fp) {
        fflush(log_fp);
        fclose(log_fp);
        log_fp = NULL;
    }
}

// 核心日志写入实现
void log_write(LogLevel level, const char *format, ...) {
    if (!log_fp) return;  // 未初始化时静默失败

    // 获取时间戳
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // 写入日志头
    fprintf(log_fp, "[%s] %-7s ", timestamp, level_strings[level]);

    // 写入用户内容
    va_list args;
    va_start(args, format);
    vfprintf(log_fp, format, args);
    va_end(args);

    // 强制刷新缓冲区（可选）
    fprintf(log_fp, "\n");
    fflush(log_fp);
}