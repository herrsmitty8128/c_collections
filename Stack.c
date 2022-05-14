//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "Stack.h"


inline void Stack_init(Stack* stack){
    LList_init((LList*)stack);
}


inline Stack* Stack_create(){
    return LList_create();
}


inline void Stack_delete(Stack* stack, void(*delete_data)(void*)){
    LList_delete(stack, delete_data);
}


inline void Stack_push(Stack* stack, void* data){
    LList_insert_before(stack, stack->head, LLNode_create(data));
}


inline void* Stack_pop(Stack* stack){
    LLNode* node = stack->head;
    void* data = node->data;
    LList_remove(stack, node);
    LLNode_delete(node, NULL);
    return data;
}


inline void Stack_pop_all(Stack* stack, void(*delete_data)(void*)){
    LList_remove_all(stack, delete_data);
}


inline void Stack_print(Stack* stack, char*(*data_to_str)(void*)){
    LList_print(stack, data_to_str);
}