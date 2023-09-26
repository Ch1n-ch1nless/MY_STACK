#include "stack.h"

error_t StackCtor(Stack* stk, const char* stk_name, const char* file, const int   line)
{
    error_t error = NO_ERR;

    #ifdef WITH_CANARY
    stk->left_canary  = LEFT_CANARY_VALUE;
    stk->right_canary = RIGHT_CANARY_VALUE;
    #endif
    stk->size = 0;
    stk->capacity = 4;

    #ifdef WITH_CANARY
    stk->data = (char*) calloc(stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t), sizeof(char));
    #endif
    #ifndef WITH_CANARY
    stk->data = (char*) calloc(stk->capacity * sizeof(elem_t), sizeof(char));
    #endif

    stk->name = stk_name;
    stk->file = file;
    stk->line = line;
    stk->status = LIVE_STACK;

    if (stk->data == nullptr) {
        error |= MEM_ALLOC_ERR;
    } else {
        #ifdef WITH_CANARY
        SetStkDataIntro(stk, INTRO_CANARY_VALUE);
        SetStkDataOutro(stk, OUTRO_CANARY_VALUE);
        #endif
    }
    for (int i = 0; i < stk->capacity; i++) {
        SetStkDataElemT(stk, i, POISON_VALUE);
    }

    #ifdef WITH_HASH
    stk->hash = CalculateStkHash((const Stack*) stk);
    #endif

    error |= StackVerify(stk);
    if (error != NO_ERR)
        PRINT_ERROR(stk, error)
    return error;
}

error_t StackDtor(Stack* stk)
{
    error_t error = StackVerify(stk);
    if (error) {
        PRINT_ERROR(stk, error)
        return error;
    }

    #ifdef WITH_CANARY
    stk->left_canary  = POISON_CANARY_VALUE;
    stk->right_canary = POISON_CANARY_VALUE;
    #endif

    if (stk->data != nullptr)
        free(stk->data);
    stk->data = nullptr;

    stk->status = KILLED_STACK;
    #ifdef WITH_HASH
    stk->hash = 0;
    #endif

    return NO_ERR;
}

error_t StackPush(Stack* stk, elem_t new_value)
{
    error_t error = StackVerify(stk);
    if (error) {
        PRINT_ERROR(stk, error);
        return error;
    }

    if (stk->size >= stk->capacity)
    {
        error |= StackRealloc(stk);
        if (error != NO_ERR) {
            PRINT_ERROR(stk, error)
            return error;
        }
    }
    SetStkDataElemT(stk, stk->size, new_value);
    stk->size++;
    #ifdef WITH_HASH
    stk->hash = CalculateStkHash(stk);
    #endif

    return NO_ERR;
}

error_t StackPop(Stack* stk, elem_t* ret_value)
{
    assert(ret_value);
    error_t error = StackVerify(stk);
    if (error) {
        PRINT_ERROR(stk, error);
        return error;
    }

    if (stk->size == 0) {
        *ret_value = POISON_VALUE;
        error |= MINUS_SIZE_ERR;
        PRINT_ERROR(stk, error)
        return error;
    }

    *ret_value = GetStkDataElemT(stk, stk->size-1);
    stk->size--;
    SetStkDataElemT(stk, stk->size, POISON_VALUE);
    #ifdef WITH_HASH
    stk->hash = CalculateStkHash((const Stack*) stk);
    #endif
    if (stk->size <= (stk->capacity / 4)) {
        error |= StackRealloc(stk);
        if (error) {
            PRINT_ERROR(stk, error);
            return error;
        }
    }
    #ifdef WITH_HASH
    stk->hash = CalculateStkHash(stk);
    #endif

    return NO_ERR;
}

error_t StackRealloc(Stack* stk)
{
    error_t error = StackVerify(stk);
    if (error) {
        PRINT_ERROR(stk, error);
        return error;
    }

    if (stk->size >= stk->capacity) {
        stk->capacity *= 2;
    } else if (stk->size < (stk->capacity / 4))  {   //consts
        stk->capacity /= 2;
    } else {
        return NO_ERR;
    }

    #ifdef WITH_CANARY
    stk->data = (char*) realloc(stk->data, stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t) + 8);
    #endif
    #ifndef WITH_CANARY
    stk->data = (char*) realloc(stk->data, stk->capacity * sizeof(elem_t));
    #endif
    if (stk->data == nullptr) {
        error |= MEM_ALLOC_ERR;
        PRINT_ERROR(stk, error)
    }

    for (size_t i = stk->size; i < stk->capacity; i++) {
        SetStkDataElemT(stk, i, POISON_VALUE);
    }
    #ifdef WITH_CANARY
    SetStkDataIntro(stk, INTRO_CANARY_VALUE);
    SetStkDataOutro(stk, OUTRO_CANARY_VALUE);
    #endif

    return NO_ERR;
}

error_t PrintStack(Stack* stk, const char* stk_name, const char* file,
                               const char* function, const int   line)
{
    error_t error = StackVerify(stk);
    PRINT_ERROR(stk, error)

    printf("Stack \"%s\": [%p] from %s(%d)\n", stk->name, stk, stk->file, stk->line);
    printf("called from file: %s(%d) in function: %s\n{\n", file, line, function);
    printf("Status of Stack: %s\n", stk->status);
    #ifdef WITH_CANARY
    printf("\tLeft Canary =  %X\n", stk->left_canary);
    printf("\tRight Canary = %X\n", stk->right_canary);
    #endif
    printf("\tSize     = %d\n", stk->size);
    printf("\tCapacity = %d\n", stk->capacity);
    #ifdef WITH_HASH
    printf("\tHash     = %u\n", stk->hash);
    #endif
    printf("\tData     = [%p]\n", stk->data);
    if (stk->data == nullptr) {
        printf("\tElements of Data: {}\n}\n");
        return NO_ERR;
    }
    printf("\tElements of Data:\n\t{\n");
    #ifdef WITH_CANARY
    printf("\t Left canary(Intro) = %X\n", GetStkDataIntro(stk));
    #endif
    for (int i = 0; i < stk->capacity; i++) {
        PrintStkDataElemT(stk, i);
    }
    #ifdef WITH_CANARY
    printf("\t Right canary(Outro) = %X\n", GetStkDataOutro(stk));
    #endif
    printf("\t}\n}\n");

    return NO_ERR;
}

