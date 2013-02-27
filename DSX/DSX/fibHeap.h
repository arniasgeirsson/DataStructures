//
//  fibHeap.h
//  DSX
//
//  Created by Arni Asgeirsson on 20/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#ifndef DSX_fibHeap_h
#define DSX_fibHeap_h

#include "Definitions.h"

#define NODE_UNMARKED 0
#define NODE_MARKED 1

typedef struct fib_heap_node_ {
    int key;
    int degree;
    int mark;
    struct fib_heap_node_ *left;
    struct fib_heap_node_ *right;
    struct fib_heap_node_ *parent;
    struct fib_heap_node_ *child;
    Data el;
} fib_heap_node;

typedef struct fib_heap_ {
    struct fib_heap_node_ *min;
    int numberOfNodes;
} fib_heap;

void fibHeap_insertNodeInLevel(fib_heap_node *levelNode, fib_heap_node *movingNode); /* Find better name */
void fibHeap_removeNodeFromLevel(fib_heap_node *removingNode); /* Find better name */

void fibHeap_printRootList(fib_heap *heap, char *offset, int dig);

fib_heap* fibHeap_make_heap();

void fibHeap_insert(fib_heap *heap, fib_heap_node *node);

fib_heap_node* fibHeap_minimum(fib_heap *heap);

float fibHeap_extract_minimum(fib_heap *heap);

fib_heap* fibHeap_union(fib_heap *heap1, fib_heap *heap2);

void fibHeap_decrease_key(fib_heap *heap, fib_heap_node *node, int newKey);

void fibHeap_delete(fib_heap *heap, fib_heap_node *node);

#endif
