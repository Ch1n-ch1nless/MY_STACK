#include "stack.h"

int main()
{
    Stack stk = {.data = nullptr,
                 .size = -1,
                 .capacity = -1};

    unsigned int error = NO_ERR;

    error = StackCtor(&stk);

    if (error != NO_ERR) {
        printf("ERROR is %d", error);
        return error;
    }

    for (int i = 0; i < 16; i++) {
        printf("===Push the Element %d===\n", i);
        error = StackPush(&stk, i);
        if (error != 0) {
            //PrintErrors(error);
            return error;
        }
        PrintStack(&stk);
    }
    printf("===========================\n");

    for (int i = 0; i < 16; i++) {
        elem_t old_value = 0;
        StackPop(&stk, &old_value);
        printf("===Pop the Element %d===\n", old_value);
        PrintStack(&stk);
    }
    printf("===========================\n");

    StackDtor(&stk);

    return 0;
}
