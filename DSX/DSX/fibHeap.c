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
    if (node1->key == node2->key && node1 != node2) {
        printf("Failed, possible: Comparing two nodes with keys: %d, %d, truth is %d\n", node1->key, node2->key, node1 == node2);
    }
    return node1 == node2;
}

void fibHeap_printRootList(fib_heap *heap, char *offset)
{
    fib_heap_node *nodeLeftOfMin = heap->min->left;
    fib_heap_node *currentNode;
    fib_heap_node *nextNode = heap->min;
    int counter = 1;
    do {
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
        if (currentNode->degree > 0)
        {
            fib_heap *tmp = fibHeap_make_heap();
            tmp->min = currentNode->children[0];
            char buffer[strlen(offset)+strlen("  ")];
            strcpy(buffer, offset);
            strcat(buffer, "  ");
            fibHeap_printRootList(tmp, buffer);
        }
        counter++;
        
    } while (!fibHeap_compareNodes(nodeLeftOfMin, currentNode));
}

void fibHeap_insert(fib_heap *heap, fib_heap_node *node)
{
    node->degree = 0;
    node->parent = NULL;
    for (int i = 0; i < MAX_NUM_OF_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    node->mark = NODE_UNMARKED;
    if (heap->min == NULL) {
        node->left = node;
        node->right = node;
        heap->min = node;
    } else {
        node->left = heap->min->left;
        node->left->right = node;
        node->right = heap->min;
        heap->min->left = node;
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

void fibHeap_exchange(fib_heap_node *x, fib_heap_node *y)
{
    //printf("######Exchanging!\n");
    /* Assuming both x and y are in the root list, and therefore have no parent. */
    /*fib_heap_node *xRight = x->right;
    fib_heap_node *yLeft = y->left;
    
    x->right = y->right;
    x->right->left = x;

    y->left = x->left;
    y->left->right = y;
    
    x->left = yLeft;
    yLeft->right = x;
    
    y->right = xRight;
    xRight->left = y;*/
    
    fib_heap_node tmp = *x;
    *x = *y;
    *y = tmp;
}

void fibHeap_link(fib_heap *heap, fib_heap_node *y, fib_heap_node *x)
{
    y->left->right = y->right;
    y->right->left = y->left;
    int xDegree = x->degree;
    
    if (xDegree == MAX_NUM_OF_CHILDREN) {
        printf("Error! x has reached max number of children %d, cannot add y as child to x!\n", MAX_NUM_OF_CHILDREN);
        return;
    }
    
    y->parent = x;
    
    if (xDegree > 0) {
        x->children[xDegree-1]->right->left = y;
        y->right = x->children[xDegree-1]->right;
        
        x->children[xDegree-1]->right = y;
        y->left = x->children[xDegree-1];
    } else {
        y->right = y;
        y->left = y;
    }
    
    x->children[xDegree] = y;
    x->degree = xDegree + 1;
    
    y->mark = NODE_UNMARKED;
}

void fibHeap_consolidate(fib_heap *heap)
{
    int max = heap->numberOfNodes;
    fib_heap_node *array[max];
    for (int i = 0; i < max; i++) {
        array[i] = NULL;
    }
    fib_heap_node *nodeLeftOfMin = heap->min->left;
    fib_heap_node *currentNode;
    fib_heap_node *nextNode = heap->min;
    if (SHOW_CONTENT || 1) {
        printf("Heap before linking:\n");
        fibHeap_printRootList(heap, "");
    }
    do {
        currentNode = nextNode;
        nextNode = nextNode->right;
        
        int degree = currentNode->degree;
        if (degree > MAX_NUM_OF_CHILDREN) {
            printf("Failed: degree = %d, key = %d\n", degree, currentNode->key);

        }
        while (array[degree] != NULL)
        {
            fib_heap_node *y = array[degree];
            if (currentNode->degree != y->degree)
            {
                printf("Failed: degree correctness: %d, x: %d, y: %d\n"
                       , y->degree == currentNode->degree, currentNode->degree, y->degree);

            }
            if (currentNode->key > y->key)
            {
//                fibHeap_exchange(currentNode,y);
                fib_heap_node tmp = *currentNode;
                *currentNode = *y;
                *y = tmp;
            }

            fibHeap_link(heap, y, currentNode);

            array[degree] = NULL;
            degree = degree + 1;
        }
        array[degree] = currentNode;
    } while (!fibHeap_compareNodes(nodeLeftOfMin, currentNode));
    if (SHOW_CONTENT || 1) {
        printf("Heap after linking:\n");
        fibHeap_printRootList(heap, "");
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
                heap->min->left->right = array[i];
                array[i]->left = heap->min->left;
                heap->min->left = array[i];
                array[i]->right = heap->min;
                if (array[i]->key < heap->min->key)
                {
                    heap->min = array[i];
                }
            }
        }
    }
    if (SHOW_CONTENT || 1) {
        printf("Heap after done:\n");
        fibHeap_printRootList(heap, "");
    }
}

fib_heap_node* fibHeap_extract_minimum(fib_heap *heap)
{
    fib_heap_node *z = heap->min;
    
    if (z != NULL) {
        printf("z has degree of %d and key of %d\n", z->degree, z->key);
        if (SHOW_CONTENT) {
            printf("Heap before adding z's children to root list:\n");
            fibHeap_printRootList(heap, "");
        }
        for (int i = 0; i < z->degree; i++)
        {
            fib_heap_node *child = z->children[i];
            child->left = heap->min->left;
            child->left->right = child;
            child->right = heap->min;
            heap->min->left = child;
            child->parent = NULL;
            z->children[i] = NULL;
            z->degree = z->degree - 1;
        }
        //z->degree = 0;
        if (SHOW_CONTENT) {
            printf("Heap after adding z's children to root list, and before removing z:\n");
            fibHeap_printRootList(heap, "");
        }
        z->left->right = z->right;
        z->right->left = z->left;

        if (fibHeap_compareNodes(z, z->right))
        {
            printf("z was last element\n");
            heap->min = NULL;
        } else {
            heap->min = z->right;
            if (SHOW_CONTENT) {
                printf("Heap after removing z, before consolidating:\n");
                fibHeap_printRootList(heap, "");
            }
            fibHeap_consolidate(heap);
            if (SHOW_CONTENT) {
                printf("Heap after consolidating:\n");
                fibHeap_printRootList(heap, "");
            }
        }
        heap->numberOfNodes = heap->numberOfNodes - 1;
    } else {
        printf("Extracting, z is null.\n");
    }
    return z;
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
    x->left->right = x->right;
    x->right->left = x->left;
    
    int removed = 0;
    
    for (int i = 0; i < y->degree; i++)
    {
        if (removed == 1)
        {
            y->children[i-1] = y->children[i];
            y->children[i] = NULL;
        } else if (fibHeap_compareNodes(y->children[i], x))
        {
            y->children[i] = NULL;
            removed = 1;
        }
    }
    
    y->degree = y->degree - 1;
    
    heap->min->left->right = x;
    x->left = heap->min->left;
    heap->min->left = x;
    x->right = heap->min;
    
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

