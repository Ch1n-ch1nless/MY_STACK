#include "stack.h"

int main()
{
    Stack stk = {.left_canary = POISON_CANARY_VALUE,
                 .data = nullptr,
                 .size = -1,
                 .capacity = -1,
                 .name = nullptr,
                 .file = nullptr,
                 .line = -1,
                 .right_canary = POISON_CANARY_VALUE};

    error_t error = NO_ERR;

    error = STACK_CTOR(&stk);
    PRINT_STACK(&stk)

    for (int i = 0; i < 4; i++) {
        error = StackPush(&stk, i);
        printf("----------------------------------------\n");
        printf("\tPush the Element [\033[32m%d\033[0m]\n", i);
        PRINT_STACK(&stk)
        printf("----------------------------------------\n");
    }

    for (int i = 0; i < 5; i++) {
        elem_t old_value = 0;
        error = StackPop(&stk, &old_value);
        printf("----------------------------------------\n");
        printf("\tPop the Element [\033[31m%d\033[0m]\n", old_value);
        PRINT_STACK(&stk)
        printf("----------------------------------------\n");
    }

    StackDtor(&stk);

    return 0;
}
