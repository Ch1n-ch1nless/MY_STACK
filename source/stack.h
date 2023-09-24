#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "errors.h"

error_t StackCtor(Stack* stk, const char* stk_name, const char* file, const int   line);
error_t StackDtor(Stack* stk);

error_t StackPush(Stack* stk, elem_t new_value);
error_t StackPop(Stack* stk, elem_t* ret_value);

error_t StackRealloc(Stack* stk);

error_t PrintStack(Stack* stk, const char* stk_name, const char* file,
                               const char* function, const int   line);

#endif // STACK_H_INCLUDED
