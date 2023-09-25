#include "test.h"

void CheckStackCanaries(Stack* stk)
{
    #ifdef WITH_CANARY
    stk->left_canary = POISON_CANARY_VALUE;
    error_t error = StackVerify(stk);
    PRINT_ERROR(stk, error);
    #endif
    return;
}

void CheckDataCanaries(Stack* stk)
{
    #ifdef WITH_CANARY
    SetStkDataOutro(stk, POISON_CANARY_VALUE);
    error_t error = StackVerify(stk);
    PRINT_ERROR(stk, error);
    #endif
    return;
}

void CheckHashStack(Stack* stk)
{
    #ifdef WITH_HASH
    SetStkDataElemT(stk, 8, 0);
    error_t error = StackVerify(stk);
    PRINT_ERROR(stk, error);
    #endif
    return;
}

void LaunchTests()
{
    Stack stk = {};
    STACK_CTOR(&stk);
    PRINT_STACK(&stk);
    CheckHashStack(&stk);
    PRINT_STACK(&stk);
}
