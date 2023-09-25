#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include "struct_and_const.h"
#include "string.h"

void CloseLogFile(FILE* log_file_ptr);

FILE* OpenLogFile(const char* file_name);

#endif // LOG_H_INCLUDED
