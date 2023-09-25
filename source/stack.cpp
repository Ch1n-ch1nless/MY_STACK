#include "stack.h"
#include "getter_setter.h"

error_t StackCtor(Stack* stk, const char* stk_name, const char* file, const int   line)
{
    error_t error = NO_ERR;

    stk->left_canary  = LEFT_CANARY_VALUE;
    stk->right_canary = RIGHT_CANARY_VALUE;
    stk->size = 0;
    stk->capacity = 4;

    stk->data = (char*) calloc(stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t), sizeof(char));

    stk->name = stk_name;
    stk->file = file;
    stk->line = line;

    if (stk->data == nullptr) {
        error |= MEM_ALLOC_ERR;
    } else {
        SetStkDataIntro(stk, INTRO_CANARY_VALUE);
        SetStkDataOutro(stk, OUTRO_CANARY_VALUE);
    }
    for (int i = 0; i < stk->capacity; i++) {
        SetStkDataElemT(stk, i, POISON_VALUE);
    }

    stk->hash = CalculateStkHash(stk);

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

    stk->left_canary  = POISON_CANARY_VALUE;
    stk->right_canary = POISON_CANARY_VALUE;

    free(stk->data);
    stk->data = nullptr;

    stk->size = -1;
    stk->capacity = -1;
    stk->name = nullptr;
    stk->file = nullptr;
    stk->line = -1;
    stk->hash = 0;

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
    if (stk->size <= (stk->capacity / 4)) {
        error |= StackRealloc(stk);
        if (error) {
            PRINT_ERROR(stk, error);
            return error;
        }
    }

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
    } else if (stk->size <= (stk->capacity / 4))  {
        stk->capacity /= 2;
    } else {
        return NO_ERR;
    }

    stk->data = (char*) realloc(stk->data, stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t));
    if (stk->data == nullptr) {
        error |= MEM_ALLOC_ERR;
        PRINT_ERROR(stk, error)
    }

    for (size_t i = stk->size; i < stk->capacity; i++) {
        SetStkDataElemT(stk, i, POISON_VALUE);
    }
    SetStkDataIntro(stk, INTRO_CANARY_VALUE);
    SetStkDataOutro(stk, OUTRO_CANARY_VALUE);

    return NO_ERR;
}

error_t PrintStack(Stack* stk, const char* stk_name, const char* file,
                               const char* function, const int   line)
{
    error_t error = StackVerify(stk);
    if (error != NO_ERR) {
        PRINT_ERROR(stk, error);
        return error;
    }

    printf("Stack \"%s\": [%p] from %s(%d)\n", stk->name, stk, stk->file, stk->line);
    printf("called from file: %s(%d) in function: %s\n{\n", file, line, function);
    printf("\tLeft Canary =  %X\n", stk->left_canary);
    printf("\tRight Canary = %X\n", stk->right_canary);
    printf("\tSize     = %d\n", stk->size);
    printf("\tCapacity = %d\n", stk->capacity);
    printf("\tData     = [%p]\n", stk->data);
    printf("\tElements of Data:\n\t{\n");
    printf("\t Left canary(Intro) = %X\n", GetStkDataIntro(stk));
    for (int i = 0; i < stk->capacity; i++) {
        PrintStkDataElemT(stk, i);
    }
    printf("\t Right canary(Outro) = %X\n", GetStkDataOutro(stk));
    printf("\t}\n}\n");

    return NO_ERR;
}

