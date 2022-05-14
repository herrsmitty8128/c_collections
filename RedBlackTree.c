//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "RedBlackTree.h"
#include <string.h>
#include <stdio.h>


/***********************************************************************
 *                            RBNode
 **********************************************************************/

RBNode* RBNode_create(RBTree* tree, void* key, void* value, bool color){
    RBNode* n = (RBNode*)malloc(sizeof(RBNode));
    if(n != NULL){
        n->pair.key = key;
        n->pair.value = value;
        n->color = color;
        n->parent = tree->nil;
        n->left = tree->nil;
        n->right = tree->nil;
    }
    return n;
}


void RBNode_delete(RBNode* node, void(*delete_kvp)(void*,void*)){
    if(delete_kvp) delete_kvp(node->pair.key, node->pair.value);
    free(node);
}


/***********************************************************************
 *                              RBTree
 **********************************************************************/


bool RBTree_init(RBTree* tree, int(*compare_keys)(void*,void*)){
    RBNode* nil = RBNode_create(tree, NULL, NULL, BLACK);
    if(nil){
        tree->nil = nil;
        tree->root = nil;
        tree->count = 0;
        tree->cmp_keys = compare_keys;
        return true;
    }
    return false;
}


RBTree* RBTree_create(int(*compare_keys)(void*,void*)){
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    if(tree){
        if(!RBTree_init(tree, compare_keys)){
            free(tree);
            tree = NULL;
        }
    }
    return tree;
}


void RBTree_delete(RBTree* tree, void(*delete_kvp)(void*,void*)){
    RBTree_remove_all(tree, delete_kvp);
    RBNode_delete(tree->nil, NULL);
    free(tree);
}


RBNode* RBTree_lookup(RBTree* tree, RBNode* node, void* key){
    while(node != tree->nil){
        int x = tree->cmp_keys(key, node->pair.key);
        if(x == 0) return node;
        node = x < 0 ? node->left : node->right;
    }
    return NULL;
}


RBNode* RBTree_min(RBTree* tree, RBNode* node){
    while(node->left != tree->nil) node = node->left;
    return node;
}


RBNode* RBNode_max(RBTree* tree, RBNode* node){
    while(node->right != tree->nil) node = node->right;
    return node;
}


RBNode* RBNode_gte(RBTree* tree, RBNode* node, void* key){
    if(node != tree->nil){
        while(1){
            if(node->left != tree->nil && tree->cmp_keys(key, node->pair.key) < 0){
                node = node->left;
                if(tree->cmp_keys(key, node->pair.key) >= 0) break;
            }
            else if(node->right != tree->nil && tree->cmp_keys(key, node->pair.key) > 0){
                node = node->right;
                if(tree->cmp_keys(key, node->pair.key) <= 0) break;
            }
            else{
                break;
            }
        }
    }
    return node;
}


RBNode* RBNode_next(RBTree* tree, RBNode* node){
    if(node != tree->nil){
        if(node->right != tree->nil){
            node = node->right;
            while(node->left != tree->nil){
                node = node->left;
            }
        }
        else{
            void* key = node->pair.key;
            do{
                node = node->parent;
            }while(node != tree->nil && tree->cmp_keys(node->pair.key, key) <= 0);
        }
    }
    return node;
}


void left_rotate(RBTree* t, RBNode* x){
    RBNode* y = x->right;
    x->right = y->left;
    if(y->left != t->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->nil){
        t->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


void right_rotate(RBTree* t, RBNode* x){
    RBNode* y = x->left;
    x->left = y->right;
    if(y->right != t->nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->nil){
        t->root = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}


void insert_fixup(RBTree* t, RBNode* z){

    RBNode* y;

    while(z->parent->color == RED){
        
        if(z->parent == z->parent->parent->left){
        
            y = z->parent->parent->right;
        
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    left_rotate(t,z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(t, z->parent->parent);
            }
        }
        else{

            y = z->parent->parent->left;
        
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    right_rotate(t,z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = BLACK;
}


bool RBTree_insert(RBTree* tree, RBNode* node){

    RBNode* z = node;
    RBNode* y = tree->nil;
    RBNode* x = tree->root;
    
    while(x != tree->nil){
        y = x;
        int result = tree->cmp_keys(z->pair.key, x->pair.key);
        if(result == 0) return false;   //the key already exists
        x = result < 0 ? x->left : x->right;
    }
    
    z->parent = y;
    
    if(y == tree->nil) tree->root = z;
    else if(tree->cmp_keys(z->pair.key, y->pair.key) < 0) y->left = z;
    else y->right = z;

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;

    insert_fixup(tree,z);
    tree->count++;
    return true;
}


void transplant(RBTree* t, RBNode* u, RBNode* v){
    if(u->parent == t->nil) t->root = v;
    else if(u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}


void delete_fixup(RBTree* t, RBNode* x){

    RBNode* w;

    while(x != t->root && x->color == BLACK){
    
        if(x == x->parent->left){
    
            w = x->parent->right;
    
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(t, x->parent);
                w = x->parent->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }

            else{
                if(w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(t,w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(t,x->parent);
                x = t->root;
            }
        }
        else{

            w = x->parent->left;
    
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(t, x->parent);
                w = x->parent->left;
            }

            else if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
            }

            else{
                if(w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(t,w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(t,x->parent);
                x = t->root;
            }
        }
    }
    x->color = BLACK;
}



void RBTree_remove(RBTree* tree, RBNode* node){

    RBNode* z = node;
    RBNode* x = NULL;
    RBNode* y = z;

    int y_original_color = y->color;
    
    if(z->left == tree->nil){
        x = z->right;
        transplant(tree, z, z->right);
    }

    else if(z->right == tree->nil){
        x = z->left;
        transplant(tree, z, z->left);
    }

    else{
        y = RBTree_min(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }
        else{
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(y_original_color == BLACK){
        delete_fixup(tree, x);
    }

    tree->count--;
}


void RBTree_remove_all(RBTree* tree, void(*delete_kvp)(void*,void*)){
    while(tree->count > 0){
        RBNode* node = tree->root;
        RBTree_remove(tree, node);
        RBNode_delete(node, delete_kvp);
    }
}
