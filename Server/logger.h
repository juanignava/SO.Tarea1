#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LOG_FILE_PATH "/var/log/doc-server.log"

void docs_log(char* fmt, ...);

#endif /* SERVER_LOGGER_H */
