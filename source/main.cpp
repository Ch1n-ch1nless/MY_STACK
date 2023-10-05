#include "stack.h"
#include "calculator.h"

int main()
{
    Stack stk = {};

    error_t error = NO_ERR;

    error = STACK_CTOR(&stk);

    CalculateExpression(&stk);

    StackDtor(&stk);

    return 0;
}
