#include "stack.h"

unsigned int StackVerify(Stack* stk)
{
    assert(stk);

    unsigned int error = 0;
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

    stk->size = 0;
    stk->capacity = 1;
    stk->data = (elem_t*) calloc(stk->capacity, sizeof(elem_t));
    if (stk->data == nullptr) {
        return MEM_ALLOC_ERR;
    }
    return NO_ERR;
}

unsigned int StackDtor(Stack* stk)
{
    assert(stk);

    unsigned int error = StackVerify(stk);
    if (error)
        return error;
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
        if (error != 0)
            return error;
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

    stk->data = (elem_t*) realloc(stk->data, stk->capacity * sizeof(elem_t));

    return NO_ERR;
}

void PrintStack(Stack* stk)
{
    assert(stk);
    assert(stk->data);

    printf("Stack: [%p]\n", stk);
    printf("\tData     = [%p]\n", stk->data);
    printf("\tSize     = %d\n", stk->size);
    printf("\tCapacity = %d\n", stk->capacity);
    printf("Elements:\n");
    for (int i = 0; i < stk->size; i++) {
        printf("\t*[%d] = " elem_format "\n", i, stk->data[i]);
    }
    for (int i = stk->size; i < stk->capacity; i++) {
        printf("\t [%d] = " elem_format "\n", i, stk->data[i]);
    }
    printf("--------------------\n");
}
