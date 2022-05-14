//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "Queue.h"


inline void Queue_init(Queue* q){
    LList_init((LList*)q);
}


inline Queue* Queue_create(){
    return (Queue*)LList_create();
}


inline void Queue_delete(Queue* q, void(*delete_data)(void*)){
    LList_delete(q, delete_data);
}


inline void Queue_enqueue(Queue* q, void* data){
    LList_insert_before(q, q->head, LLNode_create(data));
}


inline void* Queue_dequeue(Queue* q){
    QNode* node = q->tail;
    void* data = node->data;
    LList_remove(q, node);
    LLNode_delete(node, NULL);
    return data;
}


inline void Queue_dequeue_all(Queue* q, void(*delete_data)(void*)){
    LList_remove_all(q, delete_data);
}


inline void Queue_print(Queue* q, char*(*data_to_string)(void*)){
    LList_print(q, data_to_string);
}