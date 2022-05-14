//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LINKED_LIST_NODE LLNode;
typedef struct LINKED_LIST LList;

struct LINKED_LIST_NODE {
    LLNode* prev;
    LLNode* next;
    void* data;
};

struct LINKED_LIST {
    LLNode* head;
    LLNode* tail;
    size_t count;
};

LLNode* LLNode_create(void* data);
void    LLNode_delete(LLNode* n, void(*delete_data)(void*));

void    LList_init(LList* list);
LList*  LList_create();
void    LList_delete(LList* list, void(*delete_data)(void*));
LLNode* LList_search(LList* list, void* data, int(*compare_data)(void*,void*));
void    LList_insert_before(LList* list, LLNode* existing, LLNode* newNode);
void    LList_insert_after(LList* list, LLNode* existing, LLNode* newNode);
void    LList_remove(LList* list, LLNode* node);
void    LList_remove_all(LList* list, void(*delete_data)(void*));
void    LList_print(LList* list, char*(*data_to_str)(void*));

#ifdef __cplusplus
}
#endif

#endif



