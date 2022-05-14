//           Copyright Christopher Smith 2022.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCHILD(x) (2 * x) + 1
#define RCHILD(x) (2 * x) + 2
#define PARENT(x) (x - 1) / 2

typedef struct HEAP MaxHeap;
typedef struct HEAP MinHeap;

struct HEAP {
    size_t size;   // size of the array
    size_t count;  // number of elements in the array
    void*  array;
};

// should we add an iterator?????

MaxHeap* MaxHeap_create(size_t size);
void     MaxHeap_delete(MaxHeap** h, void(*delete_data)(void*));
void     MaxHeap_insert(MaxHeap* h, void* data, int(*compare_data)(void*,void*));
void*    MaxHeap_maximum(MaxHeap* h);
void*    MaxHeap_extract(MaxHeap* h);
void     MaxHeap_increase(MaxHeap* h, size_t i, void* key);

MinHeap* MinHeap_create(size_t size);
void     MinHeap_delete(MinHeap** h, void(*delete_data)(void*));
void     MinHeap_insert(MinHeap* h, void* data, int(*compare_data)(void*,void*));
void*    MinHeap_minimum(MinHeap* h);
void*    MinHeap_extract(MinHeap* h);
void     MinHeap_decrease(MinHeap* h, size_t i, void* key);

#ifdef __cplusplus
}
#endif

#endif
