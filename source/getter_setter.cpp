#include "getter_setter.h"
#include "struct_and_const.h"

canary_t GetStkDataIntro(const Stack* stk)
{
    assert(stk);
    assert(stk->data);

    canary_t* temp_ptr = (canary_t*) stk->data;
    return temp_ptr[0];
}

canary_t GetStkDataOutro(const Stack* stk)
{
    assert(stk);
    assert(stk->data);

    char* temp_ptr1 = stk->data + sizeof(canary_t) + stk->capacity * sizeof(elem_t);
    canary_t* temp_ptr = (canary_t*) temp_ptr1;
    return temp_ptr[1];
}

void SetStkDataIntro(Stack* stk, const canary_t intro_value)
{
    assert(stk);
    assert(stk->data);

    canary_t old_value = GetStkDataIntro(stk);
    canary_t* temp_ptr = (canary_t*) stk->data;
    temp_ptr[0] = intro_value;
}

void SetStkDataOutro(Stack* stk, const canary_t outro_value)
{
    assert(stk);
    assert(stk->data);

    canary_t old_value = GetStkDataOutro(stk);
    char* temp_ptr1 = stk->data + sizeof(canary_t) + stk->capacity * sizeof(elem_t);
    canary_t* temp_ptr = (canary_t*) temp_ptr1;
    temp_ptr[1] = outro_value;
}

elem_t GetStkDataElemT(const Stack* stk, const size_t index)
{
    assert(stk);
    assert(stk->data);

    canary_t* temp_ptr1 = (canary_t*) stk->data;
    temp_ptr1++;
    elem_t* temp_ptr = (elem_t*) temp_ptr1;
    return temp_ptr[index];
}

void SetStkDataElemT(Stack* stk, const size_t index, elem_t new_value)
{
    assert(stk);
    assert(stk->data);

    canary_t* temp_ptr1 = (canary_t*) stk->data;
    temp_ptr1++;
    elem_t* temp_ptr = (elem_t*) temp_ptr1;
    temp_ptr[index] = new_value;
}
