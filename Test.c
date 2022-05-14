//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "RedBlackTree.h"
#include "Queue.h"
#include <stdio.h>



void RBTree_print(RBTree* tree, void(*print_kvp)(KVPair*)){

    if (tree->root == NULL) return;
 
    // Create an empty queue for level order traversal
    Queue* q = Queue_create();
    
    Queue_enqueue(q, tree->root);
 
    while (q->count > 0){
        
        int nodeCount = q->count;
 
        // Dequeue all nodes of current level and
        // Enqueue all nodes of next level
        while (nodeCount > 0){
            RBNode* node = Queue_dequeue(q);
            print_kvp(&(node->pair));
            if (node->left != tree->nil)
                Queue_enqueue(q, node->left);
            if (node->right != tree->nil)
                Queue_enqueue(q, node->right);
            nodeCount--;
        }
        printf("\n");
    }

    Queue_delete(q,NULL);
}

int compareInt(void* a, void* b){
    int x = *((int*)a);
    int y = *((int*)b);
    if(x>y) return 1;
    if(x<y) return -1;
    return 0;
}

void print_int(KVPair* pair){
    int i = *((int*)(pair->value));
    printf("%d ",i);
}

int main(){

    // create a list of random number to use a keys and values in our test
    printf("Creating a list of random numbers\n");
    int num_keys = 1400;
    int* keyvalues = (int*)calloc(num_keys, sizeof(int));
    srand(0);
    for(int i = 0; i < num_keys; i++) keyvalues[i] = rand();

    // create a new red-black tree
    printf("Creating a new tree object.\n");
    RBTree* tree = RBTree_create(compareInt);
    if(tree==NULL){
        printf("Failed to create tree\n");
        return 0;
    }

    // insert all the keys into the tree
    printf("Inserting keys into the tree.\n");
    for(int i = 0; i < num_keys; i++){
        //printf("[%d] %d\n", i, keyvalues[i]);
        RBNode* node = RBNode_create(tree, &keyvalues[i], &keyvalues[i], RED);
        if(!RBTree_insert(tree, node)){
            printf("Failed to insert [%d] %d\n", i, keyvalues[i]);
            return 0;
        }
    }

    // lookup all the keys
    printf("Looking-up all keys.\n");
    for(int i = 0; i < num_keys; i++){
        RBNode* node = RBTree_lookup(tree, tree->root, &keyvalues[i]);
        if(node == NULL){
            printf("Unable to find [%d] %d\n", i, keyvalues[i]);
            return EXIT_SUCCESS;
        }
        if((int*)(node->pair.key) != &keyvalues[i]) printf("Did not find the correct key\n");
    }

    RBTree_print(tree, print_int);

    printf("Erasing the tree.\n");
    RBTree_remove_all(tree, NULL);

    // clean up and return
    printf("Deleting objects\n");
    RBTree_delete(tree, NULL);
    free(keyvalues);

    return EXIT_SUCCESS;

}