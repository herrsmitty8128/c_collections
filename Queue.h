//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "LinkedList.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LINKED_LIST_NODE QNode;
typedef struct LINKED_LIST Queue;

void   Queue_init(Queue* q);
Queue* Queue_create();   // calls Queue_init()
void   Queue_delete(Queue* q, void(*delete_data)(void*)); // only use with Queue_create()
void   Queue_enqueue(Queue* q, void* data);
void*  Queue_dequeue(Queue* q);
void   Queue_dequeue_all(Queue* q, void(*delete_data)(void*));
void   Queue_print(Queue* q, char*(*data_to_string)(void*));

#ifdef __cplusplus
}
#endif

#endif
