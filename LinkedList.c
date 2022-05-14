//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "LinkedList.h"
#include <stdio.h>
#include <string.h>


inline LLNode* LLNode_create(void* data){
    LLNode* node = (LLNode*)malloc(sizeof(LLNode));
    if(node){
        node->prev = NULL;
        node->next = NULL;
        node->data = data;
    }
    return node;
}


inline void LLNode_delete(LLNode* node, void(*delete_data)(void*)){
    if(delete_data) delete_data(node->data);
    free(node);
}


inline void LList_init(LList* list){
    memset(list, 0, sizeof(LList));
}


inline LList* LList_create(){
    LList* list = (LList*)malloc(sizeof(LList));
    if(list){
        LList_init(list);
    }
    return list;
}


inline void LList_delete(LList* list, void(*delete_data)(void*)){
    LList_remove_all(list, delete_data);
    free(list);
}


LLNode* LList_search(LList* list, void* data, int(*compare_data)(void*,void*)){
    LLNode* curr = list->head;
    while(curr != NULL && compare_data(data, curr->data) != 0) curr = curr->next;
    return curr;
}


inline void LList_insert_before(LList* list, LLNode* existing, LLNode* newNode){
    newNode->next = existing;
    if(existing == list->head){
        newNode->prev = NULL;
        if(list->head == NULL){
            list->tail = newNode;
        }
        else{
            existing->prev = newNode;
        }
        list->head = newNode;
    }
    else{
        newNode->prev = existing->prev;
        existing->prev->next = newNode;
        existing->prev = newNode;
    }
    list->count++;
}


inline void LList_insert_after(LList* list, LLNode* existing, LLNode* newNode){
    newNode->prev = existing;
    if(existing == list->tail){
        newNode->next = NULL;
        if(list->tail == NULL){
            list->head = newNode;
        }
        else{
            existing->next = newNode;
        }
        list->tail = newNode;
    }
    else{
        newNode->next = existing->next;
        existing->next->prev = newNode;
        existing->next = newNode;
    }
    list->count++;
}


inline void LList_remove(LList* list, LLNode* node){
    if (node->prev == NULL){
        list->head = node->next;
    }
    else {
        node->prev->next = node->next;
    }
    if (node->next == NULL){
        list->tail = node->prev;
    }
    else {
        node->next->prev = node->prev;
    }
    list->count--;
}


void LList_remove_all(LList* list, void(*delete_data)(void*)) {
    LLNode* node;
    while(list->head != NULL){
        node = list->head;
        LList_remove(list, node);
        LLNode_delete(node, delete_data);
    }
}


void LList_print(LList* list, char*(*data_to_str)(void*)){
    LLNode* curr = list->head;
    printf("[");
    while(curr != NULL){
        char* str = data_to_str(curr->data);
        printf("%s", str);
        if(curr != list->tail) printf(", ");
        curr = curr->next;
    }
    printf("]");
}
