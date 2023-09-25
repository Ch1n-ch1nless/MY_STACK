#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "stack.h"
#include "errors.h"
#include "log.h"
#include "getter_setter.h"
#include "struct_and_const.h"

void CheckStackCanaries(Stack* stk);
void CheckDataCanaries(Stack* stk);
void CheckHashStack(Stack* stk);
void LaunchTests();

#endif // TEST_H_INCLUDED
