# c_collections

*c_collections* is a library of collection algorithms written in the c programming language. It is licensed under the Boost Software License - Version 1.0 - August 17th, 2003.

## RedBlackTree

```c
typedef struct RED_BLACK_NODE RBNode;

typedef struct KEY_VALUE_PAIR {
    void* key;
    void* value;
}KVPair;

struct RED_BLACK_NODE {
    KVPair  pair;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    bool    color;
};

typedef struct RED_BLACK_TREE {
    RBNode*     nil;
    RBNode*     root;
    size_t      count;
    int(*cmp_keys)(void*,void*);
}RBTree;

RBNode* RBNode_create(RBTree* tree, void* key, void* value, bool color);
void    RBNode_delete(RBNode* node, void(*delete_kvp)(void*,void*));
bool    RBTree_init(RBTree* tree, int(*compare_keys)(void*,void*));
RBTree* RBTree_create(int(*compare_keys)(void*,void*));
void    RBTree_delete(RBTree* tree, void(*delete_kvp)(void*,void*));
RBNode* RBTree_lookup(RBTree* tree, RBNode* node, void* key);
RBNode* RBTree_min(RBTree* tree, RBNode* node);
RBNode* RBTree_max(RBTree* tree, RBNode* node);
RBNode* RBTree_gte(RBTree* tree, RBNode* node, void* key);
RBNode* RBTree_next(RBTree* tree, RBNode* node);
bool    RBTree_insert(RBTree* tree, RBNode* node);
void    RBTree_remove(RBTree* tree, RBNode* node);
void    RBTree_remove_all(RBTree* tree, void(*delete_kvp)(void*,void*));
void    RBTree_print(RBTree* tree, void(*print_kvp)(KVPair*));
```

## LinkedList

```c
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
```

## Queue

```c
typedef struct LINKED_LIST_NODE QNode;
typedef struct LINKED_LIST Queue;

void   Queue_init(Queue* q);
Queue* Queue_create();   // calls Queue_init()
void   Queue_delete(Queue* q, void(*delete_data)(void*)); // only use with Queue_create()
void   Queue_enqueue(Queue* q, void* data);
void*  Queue_dequeue(Queue* q);
void   Queue_dequeue_all(Queue* q, void(*delete_data)(void*));
void   Queue_print(Queue* q, char*(*data_to_string)(void*));

```

## Stack

```c
typedef struct LINKED_LIST_NODE SNode;
typedef struct LINKED_LIST Stack;

void   Stack_init(Stack* stack);
Stack* Stack_create();
void   Stack_delete(Stack* stack, void(*delete_data)(void*));
void   Stack_push(Stack* stack, void* data);
void*  Stack_pop(Stack* stack);
void   Stack_pop_all(Stack* stack, void(*delete_data)(void*));
void   Stack_print(Stack* stack, char*(*data_to_str)(void*));
```