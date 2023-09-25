#include "test.h"

void CheckStackCanaries(Stack* stk)
{
    stk->left_canary = POISON_CANARY_VALUE;
    error_t error = StackVerify(stk);
    PRINT_ERROR(stk, error);
}

void CheckDataCanaries(Stack* stk)
{
    SetStkDataOutro(stk, POISON_CANARY_VALUE);
    error_t error = StackVerify(stk);
    PRINT_ERROR(stk, error);
    return;
}

void CheckHashStack(Stack* stk)
{
    SetStkDataElemT(stk, 8, 0);
    error_t error = StackVerify(stk);
    PRINT_ERROR(stk, error);
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
