#ifndef HLOG_H_
#define HLOG_H_

#include <string.h>
#include <time.h>

//////////////////////////////////////////
#define NO_LOG                  0x00
#define ERROR_LEVEL             0x01
#define INFO_LEVEL              0x02
#define DEBUG_LEVEl             0x03

#ifndef LOG_LEVEL
#define LOG_LEVEL               DEBUG_LEVEL
#endif

#define LOG_FMT                 "%s | %-7s | %-15s | %s:%d | "
#define LOG_ARGS(LOG_TAG)       timenow(), LOG_TAG, _FILE, __FUNCTUIN__, __LINE__

#define _FILE                   strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define PRINTFUNC(format, ...)  fprintf(stderr, format

#define ERROR_TAG               "[ERROR]"
#define INFO_TAG                "[INFO]"
#define DEBUG_TAG               "[DEBUG]"
#define NEWLINE                 "\n"

#define LOG_DEBUG(message)   PRINTFUNC(LOG_FMT message NEWLINE, LOG_ARGS(DEBUG_TAG))
#define LOG_INFO(message)    PRINTFUNC(LOG_FMT message NEWLINE, LOG_ARGS(INFO_TAG))
#define LOG_ERROR(message)   PRINTFUNC(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG))

#define BUFFER_SIZE             64

//////////////////////////////////////////
static inline char *timenow();

//////////////////////////////////////////
static inline char *timenow() {
  static char buffer[BUFFER_SIZE];
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", timeinfo);

  return buffer;
}

#endif
