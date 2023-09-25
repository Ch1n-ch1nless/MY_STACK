#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include "getter_setter.h"
#include "log.h"

#define PRINT_ERROR(stk, error) PrintError(stk, error, __FILE__, __FUNCTION__, __LINE__);

enum ERRORS : unsigned int
{
    NO_ERR                  = 0,
    NULL_STK_ERR            = 1 << 0,
    NULL_ARR_ERR            = 1 << 1,
    MINUS_CAPACITY_ERR      = 1 << 2,
    MINUS_SIZE_ERR          = 1 << 3,
    CAPACITY_FEWER_SIZE_ERR = 1 << 4,
    OPEN_FILE_ERR           = 1 << 5,
    MEM_ALLOC_ERR           = 1 << 6,
    NULL_NAME_ERR           = 1 << 7,
    NULL_FILE_ERR           = 1 << 8,
    MINUS_LINE_ERR          = 1 << 9,
    RIGHT_CANARY_DIED       = 1 << 10,
    LEFT_CANARY_DIED        = 1 << 11,
    WRONG_INTRO_ERR         = 1 << 12,
    WRONG_OUTRO_ERR         = 1 << 13,
    WRONG_HASH              = 1 << 14,

    END_OF_ENUM
};

error_t StackVerify(Stack* stk);

   void PrintError(Stack* stk, error_t error, const char* file,
                                              const char* function,
                                              const int line);
   void PrintStkDataElemT(const Stack* stk, const size_t index);

hash_t  CalculateStkHash(const Stack* stk);

#endif // ERRORS_H_INCLUDED
