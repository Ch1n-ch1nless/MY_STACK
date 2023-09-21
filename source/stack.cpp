#include "stack.h"

unsigned int StackVerify(Stack* stk)
{
    assert(stk);

    unsigned int error = NO_ERR;
    if (stk == nullptr)
        error |= NULL_STK_ERR;
    if (stk->data == nullptr)
        error |= NULL_ARR_ERR;
    if (stk->capacity <= 0)
        error |= MINUS_CAPACITY_ERR;
    if (stk->size < 0)
        error |= MINUS_SIZE_ERR;
    if (stk->size > stk->capacity)
        error |= CAPACITY_FEWER_SIZE_ERR;

    return error;
}

unsigned int StackCtor(Stack* stk)
{
    assert(stk);
    size_t error = NO_ERR;

    stk->size = 0;
    stk->capacity = 1;
    stk->data = (elem_t*) calloc(stk->capacity, sizeof(elem_t));
    if (stk->data == nullptr) {
        error = MEM_ALLOC_ERR;
        PRINT_ERROR(stk, error)
    }
    return error;
}

unsigned int StackDtor(Stack* stk)
{
    assert(stk);

    unsigned int error = StackVerify(stk);
    if (error) {
        PRINT_ERROR(stk, error)
        return error;
    }
    free(stk->data);
    stk->data = nullptr;
    stk->size = -1;
    stk->capacity = -1;
    return NO_ERR;
}

unsigned int StackPush(Stack* stk, elem_t new_value)
{
    assert(stk);
    assert(stk->data);

    if (stk->size >= stk->capacity)
    {
        unsigned int error = StackRealloc(stk);
        if (error != NO_ERR) {
            PRINT_ERROR(stk, error)
            return error;
        }
    }
    stk->data[stk->size] = new_value;
    stk->size++;
    return (int) NO_ERR;
}

unsigned int StackPop(Stack* stk, elem_t* ret_value)
{
    assert(stk);
    assert(stk->data);
    assert(ret_value);

    if (stk->size == 0) {
        *ret_value = POISON_VALUE;
        return MINUS_SIZE_ERR;
    } else {
        *ret_value = stk->data[stk->size-1];
        stk->size--;
        stk->data[stk->size] = POISON_VALUE;
        if (stk->size <= (stk->capacity / 4)) {
            unsigned int error = StackRealloc(stk);
            if (error)
                PRINT_ERROR(stk, error);
                return error;
        }
    }
    return NO_ERR;
}

unsigned int StackRealloc(Stack* stk)
{
    assert(stk);
    assert(stk->data);

    if (stk->size >= stk->capacity) {
        stk->capacity *= 2;
    } else if (stk->size <= (stk->capacity / 4))  {
        stk->capacity /= 2;
    } else {
        return NO_ERR;
    }

    size_t error = StackVerify(stk);
    if (error != NO_ERR) {
        PRINT_ERROR(stk, error)
        return error;
    }
    stk->data = (elem_t*) realloc(stk->data, stk->capacity * sizeof(elem_t));
    for (size_t i = stk->size; i < stk->capacity; i++) {
        stk->data[i] = POISON_VALUE;
    }

    return NO_ERR;
}

unsigned int PrintStack(Stack* stk)
{
    assert(stk);

    size_t error = StackVerify(stk);
    if (error != NO_ERR) {
        PRINT_ERROR(stk, error);
        return error;
    }

    printf("Stack: [%p]\n{\n", stk);
    printf("\tSize     = %d\n", stk->size);
    printf("\tCapacity = %d\n", stk->capacity);
    printf("\tData     = [%p]\n", stk->data);
    printf("\tElements of Data:\n\t{\n");
    for (int i = 0; i < stk->size; i++) {
        printf("\t *[%d] = " elem_format "\n", i, stk->data[i]);
    }
    for (int i = stk->size; i < stk->capacity; i++) {
        printf("\t  [%d] = " elem_format "\n", i, stk->data[i]);
    }
    printf("\t}\n}\n");

    return NO_ERR;
}

void PrintError(Stack* stk, unsigned int error, const char* file, const char* function, const int line)
{
    fprintf(stderr, "In main.cpp called from %s(%d) in function: %s\n", file, line, function);

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
}

