#include "log.h"

FILE* OpenFile(const char* file_name, const char* mode)
{
    char* copy_file = strdup(file_name);

    strcat(copy_file, EXTENSION);

    FILE* log_file_ptr = fopen(copy_file, mode);

    if (log_file_ptr == nullptr)
    {
        log_file_ptr = stderr;
    }

    fprintf(log_file_ptr, "File is open\n");

    return log_file_ptr;
}

void CloseFile(FILE* log_file_ptr)
{
    fprintf(log_file_ptr, "File is close\n");

    fclose(log_file_ptr);
}
