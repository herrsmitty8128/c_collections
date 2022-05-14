//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef _STACK_
#define _STACK_

#include "LinkedList.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LINKED_LIST_NODE SNode;
typedef struct LINKED_LIST Stack;

void   Stack_init(Stack* stack);
Stack* Stack_create();
void   Stack_delete(Stack* stack, void(*delete_data)(void*));
void   Stack_push(Stack* stack, void* data);
void*  Stack_pop(Stack* stack);
void   Stack_pop_all(Stack* stack, void(*delete_data)(void*));
void   Stack_print(Stack* stack, char*(*data_to_str)(void*));

#ifdef __cplusplus
}
#endif

#endif