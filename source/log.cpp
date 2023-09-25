#include "log.h"

const char* EXTENSION = ".log";

FILE* OpenLogFile(const char* file_name)
{
    char* log_file_name = strdup(file_name);
    FILE* log_file_ptr = fopen(strcat(log_file_name, EXTENSION), "a");
    if (log_file_ptr == nullptr) {
        log_file_ptr = stderr;
        fprintf(log_file_ptr, "Program can NOT make %s.log. Errors will print in stderr\n", file_name);
        return log_file_ptr;
    }
    fprintf(log_file_ptr, "-----%s.log created in %s-----\n", file_name, __TIME__);

    return log_file_ptr;
}

void CloseLogFile(FILE* log_file_ptr)
{
    fprintf(log_file_ptr, "-----File was closed-----\n");
    if (log_file_ptr == stderr)
        fclose(log_file_ptr);
}
