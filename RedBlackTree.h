//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#include <stdlib.h>
#include <stdbool.h>

#ifndef RED
#define RED   1
#endif

#ifndef BLACK
#define BLACK 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RED_BLACK_NODE RBNode;

#ifndef KVPair 
typedef struct KEY_VALUE_PAIR {
    void* key;
    void* value;
}KVPair;
#endif

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

bool   RBTree_init(RBTree* tree, int(*compare_keys)(void*,void*));
RBTree* RBTree_create(int(*compare_keys)(void*,void*));
void    RBTree_delete(RBTree* tree, void(*delete_kvp)(void*,void*));
RBNode* RBTree_lookup(RBTree* tree, RBNode* node, void* key);
RBNode* RBTree_min(RBTree* tree, RBNode* node);
RBNode* RBTree_max(RBTree* tree, RBNode* node);
RBNode* RBTree_gte(RBTree* tree, RBNode* node, void* key);
RBNode* RBTree_next(RBTree* tree, RBNode* node);
bool   RBTree_insert(RBTree* tree, RBNode* node);
void    RBTree_remove(RBTree* tree, RBNode* node);
void    RBTree_remove_all(RBTree* tree, void(*delete_kvp)(void*,void*));
void    RBTree_print(RBTree* tree, void(*print_kvp)(KVPair*));

#ifdef __cplusplus
}
#endif

#endif