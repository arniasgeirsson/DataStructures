//
//  heap.h
//  DSX
//
//  Created by Arni Asgeirsson on 18/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#ifndef DSX_heap_h
#define DSX_heap_h

#include "Definitions.h"

#define MAX_HEAP_SIZE 10000000

typedef struct Heap_ {
    Data array[MAX_HEAP_SIZE];
    int length;
    int heap_size;
} Heap;

int parent(int index);
int leftChild(int index);
int rightChild(int index);

Heap* init_heap();
void add_Data(Heap *heap, Data el);
void max_heapify(Heap *heap, int root);
void build_max_heap(Heap *heap);
void sort_heap(Heap *heap);
void max_heap_insert(Heap *heap, Data el);
Data heap_extract_max(Heap *heap);
void heap_increase_key(Heap *heap, int index, int key);
Data heap_maximum(Heap *heap);
/* heap_min edition */
void printContent(Heap *heap);

#endif
