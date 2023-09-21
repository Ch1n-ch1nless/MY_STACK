#include "stack.h"

int main()
{
    Stack stk = {.data = nullptr,
                 .size = -1,
                 .capacity = -1};

    error_t error = NO_ERR;

    error = StackCtor(&stk);

    if (error != NO_ERR) {
        printf("ERROR is %d", error);
        return error;
    }

    for (int i = 0; i < 4; i++) {
        printf("----------------------------------------\n");
        printf("\tPush the Element [\033[32m%d\033[0m]\n", i);
        error = StackPush(&stk, i);
        if (error != 0) {
            PRINT_ERROR(&stk, error)
            return error;
        }
        PrintStack(&stk);
        printf("----------------------------------------\n");
    }
    printf("========================================\n");

    for (int i = 0; i < 5; i++) {
        elem_t old_value = 0;
        error = StackPop(&stk, &old_value);
        printf("----------------------------------------\n");
        printf("\tPop the Element [\033[31m%d\033[0m]\n", old_value);
        if (error != 0) {
            PRINT_ERROR(&stk, error)
            return error;
        }
        PrintStack(&stk);
        printf("----------------------------------------\n");
    }
    printf("========================================\n");

    StackDtor(&stk);

    return 0;
}
