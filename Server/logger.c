#include "logger.h"

void docs_log(char* fmt, ...)
{
    FILE* file;

    if (access(LOG_FILE_PATH, F_OK) == 0)
    {
        file = fopen(LOG_FILE_PATH, "a");
    }
    else
    {
        file = fopen(LOG_FILE_PATH, "w");

        if (file == NULL)
        {
            printf("File %s couldn't be created\n", LOG_FILE_PATH);
            return;
        }
    }

    time_t raw_time;
    struct tm* time_info;

    time(&raw_time);
    time_info = localtime(&raw_time);
    char* str_time = asctime(time_info);
    str_time[strlen(str_time) - 1] = '\0';

    fprintf(file, "%s DocServer - ", str_time);
    va_list args;
    va_start(args, fmt);
    vfprintf(file, fmt, args);
    va_end(args);
    //fprintf(file, "\n");

    fclose(file);
}
