#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define elem_t int
#define elem_format "%d"

#include <math.h>
#include <stdio.h>
#include <TXLib.h>

struct Stack
{
    elem_t* data;
    int size;
    int capacity;
};

enum ERRORS
{
    NO_ERR                  = 0,
    NULL_STK_ERR            = 1,
    NULL_ARR_ERR            = 2,
    MINUS_CAPACITY_ERR      = 4,
    MINUS_SIZE_ERR          = 8,
    CAPACITY_FEWER_SIZE_ERR = 16,
    OPEN_FILE_ERR           = 32,
    MEM_ALLOC_ERR           = 64
};

const elem_t POISON_VALUE = -1;

unsigned int StackVerify(Stack* stk);
unsigned int StackCtor(Stack* stk);
unsigned int StackDtor(Stack* stk);
unsigned int StackPush(Stack* stk, elem_t new_value);
unsigned int StackPop(Stack* stk, elem_t* ret_value);
unsigned int StackRealloc(Stack* stk);
void PrintStack(Stack* stk);
void StackCopy(Stack* dest, Stack* src);

#endif // STACK_H_INCLUDED
