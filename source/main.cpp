#include "stack.h"

int main()
{
    Stack stk = {};

    error_t error = NO_ERR;

    error = STACK_CTOR(&stk);
    PRINT_STACK(&stk)

    for (int i = 0; i < 8; i++) {
        elem_t c = i + '0';
        error = StackPush(&stk, c);
        printf("----------------------------------------\n");
        printf("\tPush the Element [\033[32m" elem_format "\033[0m]\n", c);
        PRINT_STACK(&stk)
        printf("----------------------------------------\n");
    }

    for (int i = 0; i < 9; i++) {
        elem_t old_value = 0;
        error = StackPop(&stk, &old_value);
        printf("----------------------------------------\n");
        printf("\tPop the Element [\033[31m" elem_format "\033[0m]\n", old_value);
        PRINT_STACK(&stk)
        printf("----------------------------------------\n");
    }

    StackDtor(&stk);
    PRINT_STACK(&stk);
    printf("Error is %ld\n", StackVerify(&stk));

    return 0;
}
