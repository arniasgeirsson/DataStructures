//
//  fibHeap.c
//  DSX
//
//  Created by Arni Asgeirsson on 20/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "fibHeap.h"
#include <string.h>
#include <time.h>
#include <math.h>

#define SHOW_CONTENT 0

fib_heap* fibHeap_make_heap()
{
    fib_heap* newHeap = (fib_heap*)malloc(sizeof(fib_heap));
    newHeap->min = NULL;
    newHeap->numberOfNodes = 0;
    return newHeap;
}

int fibHeap_compareNodes(fib_heap_node *node1, fib_heap_node *node2)
{
    if (node1 == NULL || node2 == NULL) {
        return node1 == node2;
    }
    if (node1->key == node2->key && node1 != node2 && SHOW_CONTENT) {
        printf("Failed, possible: Comparing two nodes with keys: %d, %d, truth is %d\n", node1->key, node2->key, node1 == node2);
    }
    return node1 == node2;
}

void fibHeap_insertNodeInLevel(fib_heap_node *levelNode, fib_heap_node *movingNode) /* Find better name */
{
    levelNode->left->right = movingNode;
    movingNode->left = levelNode->left;
    levelNode->left = movingNode;
    movingNode->right = levelNode;
}

void fibHeap_removeNodeFromLevel(fib_heap_node *removingNode)
{
    removingNode->left->right = removingNode->right;
    removingNode->right->left = removingNode->left;
}

void fibHeap_printRootList(fib_heap *heap, char *offset, int dig)
{
    if (heap->min == NULL) {
        printf("Heap is empty!\n");
        return;
    }
    fib_heap_node *nodeLeftOfMin = heap->min->left;
    fib_heap_node *currentNode;
    fib_heap_node *nextNode = heap->min;
    int counter = 1;
    do {
        if (counter > heap->numberOfNodes+1) {
            printf("Counter is to big, possible infinity loop, breaking print loop\n");
            break;
        }
        currentNode = nextNode;
        nextNode = nextNode->right;
        printf("%s", offset);
        if (counter < 10) { printf("0%d: ", counter);} else { printf("%d: ",counter); }

        int leftkey = currentNode->left->key;
        int key = currentNode->key;
        int rightkey = currentNode->right->key;
        if (leftkey < 10) { printf("0%d ", leftkey);} else { printf("%d ",leftkey); }
        if (key < 10) { printf("<-_0%d_-> ", key);} else { printf("<-_%d_-> ",key); }
        if (rightkey < 10) { printf("0%d,", rightkey);} else { printf("%d,",rightkey); }

        printf(" degree: %d, mark: %d, has parent: %d\n", currentNode->degree, currentNode->mark, currentNode->parent != NULL);
        if (currentNode->degree > 0 && dig)
        {
            fib_heap *tmp = fibHeap_make_heap();
            tmp->min = currentNode->child;
            char buffer[strlen(offset)+strlen("  ")];
            strcpy(buffer, offset);
            strcat(buffer, "  ");
            fibHeap_printRootList(tmp, buffer, 1);
        }
        counter++;
    } while (!fibHeap_compareNodes(nodeLeftOfMin, currentNode));
}

void fibHeap_insert(fib_heap *heap, fib_heap_node *node)
{
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->mark = NODE_UNMARKED;
    if (heap->min == NULL) {
        node->left = node;
        node->right = node;
        heap->min = node;
    } else {
        fibHeap_insertNodeInLevel(heap->min, node);
        if (node->key < heap->min->key) {
            heap->min = node;
        }
    }
    heap->numberOfNodes = heap->numberOfNodes + 1;
}

fib_heap_node* fibHeap_minimum(fib_heap *heap)
{
    return heap->min;
}

void fibHeap_link(fib_heap *heap, fib_heap_node *y, fib_heap_node *x)
{
    int xDegree = x->degree;
    
    y->parent = x;
    
    if (xDegree > 0) {
        fibHeap_insertNodeInLevel(x->child, y);
    } else {
        y->right = y;
        y->left = y;
        x->child = y;
    }
    
    x->degree = xDegree + 1;
    
    y->mark = NODE_UNMARKED;
    
    /* Shouldn't make any difference. */
    if (fibHeap_compareNodes(heap->min, y))
    {
        heap->min = x;
    }
}

float fibHeap_consolidate(fib_heap *heap)
{
    clock_t start = clock();
    int max = floorf(log10f(heap->numberOfNodes)/log10f((1.0+sqrtf(5.0))/2.0));
    fib_heap_node *array[max];
    for (int i = 0; i < max; i++) {
        array[i] = NULL;
    }
    clock_t end = clock();
    fib_heap_node *nodeLeftOfMin = heap->min->left;
    fib_heap_node *currentNode;
    fib_heap_node *next = heap->min;
    if (SHOW_CONTENT) {
        printf("Heap before array degree part:\n");
        fibHeap_printRootList(heap, "", 1);
    }
    
    do {
        currentNode = next;
        next = next->right;
        
        int degree = currentNode->degree;
        if (SHOW_CONTENT && degree > heap->numberOfNodes) {
            printf("Failed: degree = %d, key = %d\n", degree, currentNode->key);

        }
        while (array[degree] != NULL)
        {
            fib_heap_node *y = array[degree];
            if (SHOW_CONTENT && currentNode->degree != y->degree)
            {
                printf("Failed: degree correctness: %d, x: %d, y: %d\n"
                       , y->degree == currentNode->degree, currentNode->degree, y->degree);

            }
            if (currentNode->key > y->key)
            {
                fib_heap_node tmp = *currentNode;
                *currentNode = *y;
                *y = tmp;
            }
            if (SHOW_CONTENT) {
                printf("Heap before linking:\n");
                fibHeap_printRootList(heap, "", 1);
            }
            fibHeap_link(heap, y, currentNode);
            if (SHOW_CONTENT) {
                printf("Heap after linking:\n");
                fibHeap_printRootList(heap, "", 1);
            }
            array[degree] = NULL;
            degree = degree + 1;
        }
        array[degree] = currentNode;
    } while (!fibHeap_compareNodes(nodeLeftOfMin, currentNode));
    if (SHOW_CONTENT) {
        printf("Heap after array degree part:\n");
        fibHeap_printRootList(heap, "", 1);
    }
    heap->min = NULL;
    for (int i = 0; i < max; i++)
    {
        if (array[i] != NULL)
        {
            if (heap->min == NULL)
            {
                array[i]->left = array[i];
                array[i]->right = array[i];
                heap->min = array[i];
            } else {
                fibHeap_insertNodeInLevel(heap->min, array[i]);
                if (array[i]->key < heap->min->key)
                {
                    heap->min = array[i];
                }
            }
        }
    }
    if (SHOW_CONTENT) {
        printf("Heap after done:\n");
        fibHeap_printRootList(heap, "", 1);
    }
    return (float)(end-start)/ CLOCKS_PER_SEC;
}

float fibHeap_extract_minimum(fib_heap *heap)
{
    fib_heap_node *z = heap->min;
    float time = 0;
    if (z != NULL) {
        if (SHOW_CONTENT) {
            printf("Heap before adding z's children to root list:\n");
            fibHeap_printRootList(heap, "", 1);
        }
        
        if (z->degree > 0) {
            fib_heap_node *currentNode;
            fib_heap_node *nextNode = z->child;
            do {
                if (z->degree == 0) {
                    printf("Degree of z == 0, force break children-while-loop.\n");
                    break;
                }
                currentNode = nextNode;
                nextNode = currentNode->right;
                
                currentNode->parent = NULL;
                
                fibHeap_removeNodeFromLevel(currentNode);
                
                fibHeap_insertNodeInLevel(heap->min, currentNode);
                z->degree = z->degree - 1;
            } while (z->degree > 0);
            z->degree = 0;
            z->child = NULL;
        }
        
        if (SHOW_CONTENT) {
            printf("Heap after adding z's children to root list, and before removing z:\n");
            fibHeap_printRootList(heap, "", 1);
        }
        
        fibHeap_removeNodeFromLevel(z);
        if (fibHeap_compareNodes(z, z->right))
        {
            printf("z was last element\n");
            heap->min = NULL;
        } else {
            heap->min = z->right;
            if (SHOW_CONTENT) {
                printf("Heap after removing z, before consolidating:\n");
                fibHeap_printRootList(heap, "", 1);
            }
            time = fibHeap_consolidate(heap);
            if (SHOW_CONTENT) {
                printf("Heap after consolidating:\n");
                fibHeap_printRootList(heap, "", 1);
            }
        }
        heap->numberOfNodes = heap->numberOfNodes - 1;
    } else {
        printf("Extracting, z is null.\n");
    }
    if (SHOW_CONTENT) {
        printf("Heap after extracting:\n");
        fibHeap_printRootList(heap, "", 1);
    }
    return time;
}

/* Remember to clean up heap1 and heap2 after using this function */
fib_heap* fibHeap_union(fib_heap *heap1, fib_heap *heap2)
{
    fib_heap *newHeap = fibHeap_make_heap();
    
    newHeap->min = heap1->min;
    
    if (heap1->min != NULL && heap2->min != NULL)
    {
        heap1->min->left->right = heap2->min->right;
        heap2->min->right->left = heap1->min->left;
        
        heap1->min->left = heap2->min;
        heap2->min->right = heap1->min;
    }

    if (heap1->min == NULL || (heap2->min != NULL && heap2->min->key < heap1->min->key))
    {
        newHeap->min = heap2->min;
    }
    newHeap->numberOfNodes = heap1->numberOfNodes + heap2->numberOfNodes;
    return newHeap;
}

void fibHeap_cut(fib_heap *heap, fib_heap_node *x, fib_heap_node *y)
{
    fibHeap_removeNodeFromLevel(x);
    y->degree = y->degree - 1;
    
    fibHeap_insertNodeInLevel(heap->min, x);
    x->parent = NULL;
    x->mark = NODE_UNMARKED;
}

void fibHeap_cascading_cut(fib_heap *heap, fib_heap_node *y)
{
    fib_heap_node *z = y->parent;
    if (z != NULL)
    {
        if (y->mark == NODE_UNMARKED)
        {
            y->mark = NODE_MARKED;
        } else {
            fibHeap_cut(heap, y, z);
            fibHeap_cascading_cut(heap, z);
        }
    }
}

void fibHeap_decrease_key(fib_heap *heap, fib_heap_node *node, int newKey)
{
    if (newKey > node->key)
    {
        printf("Error: Cannot decrease key, new key is higher than old key.\n");
        return;
    }
    
    node->key = newKey;
    
    fib_heap_node *y = node->parent;
    
    if (y != NULL && node->key < y->key)
    {
        fibHeap_cut(heap, node, y);
        fibHeap_cascading_cut(heap, y);
    }
    if (node->key < heap->min->key)
    {
        heap->min = node;
    }
}

void fibHeap_delete(fib_heap *heap, fib_heap_node *node)
{
    fibHeap_decrease_key(heap, node, heap->min->key-1000);
    fibHeap_extract_minimum(heap);
}

