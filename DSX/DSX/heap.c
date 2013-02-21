//
//  heap.c
//  DSX
//
//  Created by Arni Asgeirsson on 18/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <math.h>

int parent(int index)
{
    return floorf(index/2); // Do at bit level? its faster
}

int leftChild(int index)
{
    return 2*index; // Do at bit level? its faster
}

int rightChild(int index)
{
    return 2*index+1; // Do at bit level? its faster
}

void exchange_heap(Heap *heap, int a, int b)
{
    /* See page 166, 6.5-6 for possible hints of optimization(?) */
    Data x = heap->array[a];
    heap->array[a] = heap->array[b];
    heap->array[b] = x;
}

Heap* init_heap()
{
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    return heap;
}


void add_Data(Heap *heap, Data el)
{
    if (heap->length == MAX_HEAP_SIZE) {
        printf("Heap is at max size %d, you cannot add anymore data.\n", MAX_HEAP_SIZE);
        return;
    }
    
    heap->array[heap->length] = el;
    heap->length = heap->length+1;
}

int compareHeapInts(Data a, Data b)
{
    return (*(int*)a) > (*(int*)b);
}

int compareHeapInts2(Data a, Data b)
{
    return (*(int*)a) < (*(int*)b);
}

void max_heapify(Heap *heap, int root)
{
    /* See page 156, 6.2-5 for optimization notes. (Use loop instead of recursion.) */
    int l = leftChild(root);
    int r = rightChild(root);
    int largest;
    
    if (l < heap->heap_size && compareHeapInts(heap->array[l], heap->array[root]))
    {
        largest = l;
    } else {
        largest = root;
    }
    if (r < heap->heap_size && compareHeapInts(heap->array[r], heap->array[largest]))
    {
        largest = r;
    }
    if (largest != root) {
        exchange_heap(heap, root, largest);
        max_heapify(heap, largest);
    }
}

void build_max_heap(Heap *heap)
{
    heap->heap_size = heap->length;
    for (int i = floorf(heap->length/2)-1; i >= 0; i--) {
        max_heapify(heap, i);
    }
}

void sort_heap(Heap *heap)
{
    build_max_heap(heap);
    for (int i = heap->length-1; i > 0; i--) {
        exchange_heap(heap, 0, i);
        heap->heap_size = heap->heap_size-1;
        max_heapify(heap, 0);
    }
}

void max_heap_insert(Heap *heap, Data el)
{
    heap->heap_size = heap->heap_size+1;
    heap->array[heap->heap_size-1] = el;
    *(int*)(heap->array[heap->heap_size-1]) = (*(int*)el) - 1;
    heap_increase_key(heap, heap->heap_size-1, (*(int*)el)+1);
    heap->length = heap->length+1;
}

Data heap_extract_max(Heap *heap)
{
    if (heap->heap_size < 1)
    {
        printf("Extract Max: Heap is empty!\n");
        return NULL;
    }
    Data max = heap->array[0];
    
    heap->heap_size = heap->heap_size-1;
    heap->array[0] = heap->array[heap->heap_size];
    max_heapify(heap, 0);
    return max;
}

void heap_increase_key(Heap *heap, int index, int key)
{
    if (key <= *(int*)heap->array[index])
    {
        printf("Error: Key is smaller or equal too current key!\n");
        return;
    }
    *(int*)(heap->array[index]) = key;
    
    while (index > 0 && compareHeapInts2(heap->array[parent(index)], heap->array[index]))
    {
        exchange_heap(heap, index, parent(index));
        index = parent(index);
    }    
}

Data heap_maximum(Heap *heap)
{
    if (heap->heap_size < 1)
    {
        printf("Maximum: Heap is empty!\n");
        return NULL;
    }
    return heap->array[0];
}

Heap* heap_union(Heap *heap1, Heap *heap2)
{
    /* Unions two heaps, kills the two, and returns a new one. */
    return NULL;
}

void printContent(Heap *heap)
{
    for (int i = 0; i < heap->length; i++) {
        printf("heap[%d] = %d\n", i, *(int*)(heap->array[i]));
    }
}

