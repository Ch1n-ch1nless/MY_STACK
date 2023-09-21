#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef int elem_t;
#define elem_format "%d"

#define PRINT_ERROR(stk, error) PrintError(stk, error, __FILE__, __FUNCTION__, __LINE__);

typedef unsigned long long error_t;

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    elem_t* data;
    int size;
    int capacity;
};

enum ERRORS : unsigned int
{
    NO_ERR                  = 0,
    NULL_STK_ERR            = 1,
    NULL_ARR_ERR            = 2,
    MINUS_CAPACITY_ERR      = 4,
    MINUS_SIZE_ERR          = 8,
    CAPACITY_FEWER_SIZE_ERR = 16,
    OPEN_FILE_ERR           = 32,
    MEM_ALLOC_ERR           = 64,

    END_OF_ENUM
};

const elem_t POISON_VALUE = -1;                                                             // also to StackElemParameters

error_t StackVerify(Stack* stk);

error_t StackCtor(Stack* stk);
error_t StackDtor(Stack* stk);

error_t StackPush(Stack* stk, elem_t new_value);
error_t StackPop(Stack* stk, elem_t* ret_value);

error_t StackRealloc(Stack* stk);

error_t PrintStack(Stack* stk);
   void PrintError(Stack* stk, error_t error, const char* file,
                                              const char* function,
                                              const int line);

#endif // STACK_H_INCLUDED
