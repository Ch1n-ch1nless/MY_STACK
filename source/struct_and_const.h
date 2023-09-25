#ifndef STRUCT_AND_CONST_H_INCLUDED
#define STRUCT_AND_CONST_H_INCLUDED

typedef double elem_t;
#define elem_format "%f"

#define PRINT_STACK(stk) PrintStack((stk), #stk, __FILE__, __FUNCTION__, __LINE__);
#define STACK_CTOR(stk) StackCtor((stk), #stk, __FILE__, __LINE__);

typedef unsigned long long error_t;
typedef unsigned int canary_t;
typedef unsigned int hash_t;

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const elem_t POISON_VALUE = NAN;
const canary_t LEFT_CANARY_VALUE   = 0x602DA617;
const canary_t RIGHT_CANARY_VALUE  = 0x602DABAD;
const canary_t INTRO_CANARY_VALUE  = 0xD134CA75;
const canary_t OUTRO_CANARY_VALUE  = 0x06B16A55;
const canary_t POISON_CANARY_VALUE = 0xF331D3AD;

struct Stack
{
    canary_t left_canary;
    char* data;
    int size;
    int capacity;
    const char* name;
    const char* file;
    int line;
    hash_t hash;
    canary_t right_canary;
};

#endif // STRUCT_AND_CONST_H_INCLUDED
