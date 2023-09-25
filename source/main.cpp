#include "stack.h"
#include "test.h"

#ifndef TEST_MODE
int main()
{
    Stack stk = {.left_canary = POISON_CANARY_VALUE,
                 .data = nullptr,
                 .size = -1,
                 .capacity = -1,
                 .name = nullptr,
                 .file = nullptr,
                 .line = -1,
                 .hash = 0,
                 .right_canary = POISON_CANARY_VALUE};

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

    return 0;
}
#endif
#ifdef TEST_MODE
int main()
{
    LaunchTests();
    return 0;
}
#endif
