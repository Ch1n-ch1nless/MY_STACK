#include "errors.h"

error_t StackVerify(Stack* stk)
{
    error_t error = NO_ERR;
    if (stk == nullptr) {
        error |= NULL_STK_ERR;
        return error;
    }
    if (stk->data == nullptr)
        error |= NULL_ARR_ERR;
    if (stk->capacity <= 0)
        error |= MINUS_CAPACITY_ERR;
    if (stk->size < 0)
        error |= MINUS_SIZE_ERR;
    if (stk->size > stk->capacity)
        error |= CAPACITY_FEWER_SIZE_ERR;
    if (stk->name == nullptr)
        error |= NULL_NAME_ERR;
    if (stk->file == nullptr)
        error |= NULL_FILE_ERR;
    if (stk->line <= 0)
        error |= MINUS_LINE_ERR;
    if (stk->left_canary != LEFT_CANARY_VALUE)
        error |= LEFT_CANARY_DIED;
    if (stk->right_canary != RIGHT_CANARY_VALUE)
        error |= RIGHT_CANARY_DIED;
    if (GetStkDataIntro(stk) != INTRO_CANARY_VALUE)
        error |= WRONG_INTRO_ERR;
    if (GetStkDataOutro(stk) != OUTRO_CANARY_VALUE)
        error |= WRONG_OUTRO_ERR;

    return error;
}

void PrintStkDataElemT(const Stack* stk, const size_t index)
{
    assert(stk);
    assert(stk->data);
    assert(index <= stk->capacity);

    if (index < stk->size) {
        printf("\t *[%d] = " elem_format "\n", index, GetStkDataElemT(stk, index));
    } else {
        printf("\t  [%d] = " elem_format " [POISON VALUE]\n", index, GetStkDataElemT(stk, index));
    }

}

void PrintError(Stack* stk, error_t error, const char* file, const char* function, const int line)
{
    fprintf(stderr, "In %s(%d) called from %s(%d) in function: %s\n",stk->file, stk->line, file, line, function);

    if (error & OPEN_FILE_ERR) {
        printf("Program can NOT open file\n");
    }
    if (error & MEM_ALLOC_ERR) {
        printf("Program can NOT allocate memory\n");
    }
    if (error & NULL_STK_ERR) {
        printf("Pointer to Stack is nullptr\n");
        return;
    }
    if (error & NULL_ARR_ERR) {
        printf("Pointer to array in Stack is nullptr\n");
    }
    if (error & MINUS_CAPACITY_ERR) {
        printf("Capacity in Stack = %d\n", stk->capacity);
    }
    if (error & MINUS_SIZE_ERR) {
        printf("Size in Stack = %d\n", stk->size);
    }
    if (error & CAPACITY_FEWER_SIZE_ERR) {
        printf("Size in Stack     = %d\n"
               "Capacity in Stack = %d\n"
               "Capacity < Size\n", stk->size, stk->capacity);
    }
    if (error & NULL_NAME_ERR) {
        printf("Pointer to name of string is nullptr\n");
    }
    if (error & NULL_FILE_ERR) {
        printf("Pointer to name of string is nullptr\n");
    }
    if (error & MINUS_LINE_ERR) {
        printf("The line in file, which was made stack is %d\n", stk->line);
    }
    if (error & LEFT_CANARY_DIED) {
        printf("In stack value of left canary: %X != %X\n", stk->left_canary, LEFT_CANARY_DIED);
    }
    if (error & RIGHT_CANARY_DIED) {
        printf("In stack value of right canary: %X != %X\n", stk->right_canary, RIGHT_CANARY_DIED);
    }
    if (error & WRONG_INTRO_ERR) {
        printf("In stack->data value of left canary: %X != %X\n", GetStkDataIntro(stk),
                                                                  INTRO_CANARY_VALUE);
    }
    if (error & WRONG_OUTRO_ERR) {
        printf("In stack->data value of right canary: %X != %X\n", GetStkDataOutro(stk),
                                                                  OUTRO_CANARY_VALUE);
    }
}
