///@file log.h
#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Pointer to string: ".log"
 */
static const char* EXTENSION = ".log";

/**
 *@brief Open file with extension = EXTENSION(constant in log.h)
 *
 *@param [in] file - string, which contains name of file without extension
 *@param [in] mode - string, which contains the mode of reading the file
 *
 *@return log_file_ptr - pointer on file with extension = EXTENSION
 */
FILE* OpenFile(const char* file_name, const char* mode);
/**
 *@brief Close the file
 *
 *@param [in] log_file_ptr - pointer on file, which will close
 */
void CloseFile(FILE* log_file_ptr);

#endif // LOG_H_INCLUDED
