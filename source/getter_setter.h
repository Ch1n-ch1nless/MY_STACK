#ifndef GETTER_SETTER_H_INCLUDED
#define GETTER_SETTER_H_INCLUDED

#include "struct_and_const.h"

canary_t GetStkDataIntro(const Stack* stk);
canary_t GetStkDataOutro(const Stack* stk);
    void SetStkDataIntro(Stack* stk, const canary_t new_value);
    void SetStkDataOutro(Stack* stk, const canary_t new_value);

elem_t GetStkDataElemT(const Stack* stk, const size_t index);
  void SetStkDataElemT(Stack* stk, const size_t index, elem_t new_value);

#endif // GETTER_SETTER_H_INCLUDED
