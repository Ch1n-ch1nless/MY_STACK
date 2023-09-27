#include "errors.h"

error_t StackVerify(Stack* stk)
{
    error_t error = 0;
    if (stk == nullptr) {
        error |= NULL_STK_ERR;
        return error;
    }
    if (!strcmp(stk->status, KILLED_STACK)) {
        error |= STK_KILL_ERR;
    } else if (strcmp(stk->status, LIVE_STACK) != 0) {
        error |= WRONG_STK_STATUS_ERR;
    }
    if (stk->data == nullptr)
        error |= NULL_ARR_ERR;
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
    #ifdef WITH_CANARY
    if (stk->left_canary != LEFT_CANARY_VALUE)
        error |= LEFT_CANARY_DIED;
    if (stk->right_canary != RIGHT_CANARY_VALUE)
        error |= RIGHT_CANARY_DIED;
    if (GetStkDataIntro(stk) != INTRO_CANARY_VALUE)
        error |= WRONG_INTRO_ERR;
    if (GetStkDataOutro(stk) != OUTRO_CANARY_VALUE)
        error |= WRONG_OUTRO_ERR;
    #endif
    #ifdef WITH_HASH
    if (stk->hash != CalculateStkHash(stk))
        error |= WRONG_HASH;
    #endif

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
        fprintf(stderr, "Program can NOT open file\n");
    }
    if (error & MEM_ALLOC_ERR) {
        fprintf(stderr, "Program can NOT allocate memory\n");
    }
    if (error & NULL_STK_ERR) {
        fprintf(stderr, "Pointer to Stack is nullptr\n");
        return;
    }
    if (error & STK_KILL_ERR) {
        fprintf(stderr, "Stack \"%s\" is killed!\n", stk->name);
    }
    if (error & WRONG_STK_STATUS_ERR) {
        fprintf(stderr, "Stack \"%s\" is wrong!\n", stk->name);
    }
    if (error & NULL_ARR_ERR) {
        fprintf(stderr, "Pointer to array in Stack is nullptr\n");
    }
    if (error & MINUS_CAPACITY_ERR) {
        fprintf(stderr, "Capacity in Stack = %d\n", stk->capacity);
    }
    if (error & MINUS_SIZE_ERR) {
        fprintf(stderr, "Size in Stack = %d\n", stk->size);
    }
    if (error & CAPACITY_FEWER_SIZE_ERR) {
        fprintf(stderr, "Size in Stack     = %d\n"
                              "Capacity in Stack = %d\n"
                              "Capacity < Size\n", stk->size, stk->capacity);
    }
    if (error & NULL_NAME_ERR) {
        fprintf(stderr, "Pointer to name of string is nullptr\n");
    }
    if (error & NULL_FILE_ERR) {
        fprintf(stderr, "Pointer to file of string is nullptr\n");
    }
    if (error & MINUS_LINE_ERR) {
        fprintf(stderr, "The line in file, which was made stack is %d\n", stk->line);
    }
    #ifdef WITH_CANARY
    if (error & LEFT_CANARY_DIED) {
        fprintf(stderr, "In stack value of left canary: %X != %X\n", stk->left_canary, LEFT_CANARY_VALUE);
    }
    if (error & RIGHT_CANARY_DIED) {
        fprintf(stderr, "In stack value of right canary: %X != %X\n", stk->right_canary, RIGHT_CANARY_VALUE);
    }
    if (error & WRONG_INTRO_ERR) {
        fprintf(stderr, "In stack->data value of left canary: %X != %X\n", GetStkDataIntro(stk),
                                                                                 INTRO_CANARY_VALUE);
    }
    if (error & WRONG_OUTRO_ERR) {
        fprintf(stderr, "In stack->data value of right canary: %X != %X\n", GetStkDataOutro(stk),
                                                                                  OUTRO_CANARY_VALUE);
    }
    #endif
    #ifdef WITH_HASH
    if (error & WRONG_HASH) {
        fprintf(stderr, "Error with count of hash:\n\tstk->hash = %u\n\thash =      %u\n",
                                                                                    stk->hash,
                                                                                    CalculateStkHash(stk));
    }
    #endif
}

hash_t CalculateStkHash(const Stack* stk)
{
    hash_t hash = 5381;

    hash = hash * 33 + *(hash_t*)&stk;

    hash = hash * 33 + *(hash_t*)&(stk->data);

    for (size_t i = 0; i < stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t); i++)
    {
        hash = hash * 33 + stk->data[i];
    }

    #ifdef WITH_CANARY
    hash = hash * 33 + stk->left_canary;
    hash = hash * 33 + stk->right_canary;
    #endif
    hash = hash * 33 + stk->size;
    hash = hash * 33 + stk->capacity;
    hash = hash * 33 + stk->line;
    hash = hash * 33 + *(hash_t*)&(stk->name);
    hash = hash * 33 + *(hash_t*)&(stk->file);

    return hash;
}
