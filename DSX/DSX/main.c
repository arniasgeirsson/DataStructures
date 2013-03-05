
//
//  main.c
//  DataStructures
//
//  Created by Arni Asgeirsson on 12/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "LinkedList.h"
#include "ArrayQueue.h"
#include "testQueue.h"
#include "heap.h"
#include "fibHeap.h"
#include "vEBTree.h"
#include "proto_vEBTree.h"

int number(Data el)
{
    return *(int*)el;
}

void printData(Data el)
{
    printf("Data: %d\n", *(int*)el);
}

void testQueue()
{
  
    QNode *queue = NULL;
    Data el1;
    Data el2;
    Data el3;
    Data el4;
    int a1 = 8;
    int a2 = 2;
    int a3 = 10;
    int a4 = 7;
    el1 = &a1;
    el2 = &a2;
    el3 = &a3;
    el4 = &a4;
    int b = - 1;
    int c;
    b = length(queue);
    printf("Length: %d\n", b);
    
    enqueue(&queue, el1);
    b = sum(queue, number);
    printf("1Sum: %d\n", b);
    
    enqueue(&queue, el2);
    b = sum(queue, number);
    printf("2Sum: %d\n", b);
    
    enqueue(&queue, el3);
    b = sum(queue, number);
    printf("3Sum: %d\n", b);
    
    enqueue(&queue, el4);
    printf("Lengt11h: %d\n", b);
    
    b = length(queue);
    printf("Length: %d\n", b);
    
    b = sum(queue, number);
    printf("Sum: %d\n", b);
    
    b = length(queue);
    printf("Length: %d\n", b);
    
    b = sum(queue, number);
    printf("Sum: %d\n", b);
    
    Data h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    
    h = dequeue(&queue);
    b = length(queue);
    c = sum(queue, number);
    
    if (h != NULL) {
        printf("%d, len: %d, sum: %d\n", *(int*)h,b,c);
    } else {
        printf("The queue is empty\n");
    }
  
}

void testLinkedList()
{
    LinkedList *list = NULL;
    
    lengthL(list);
    
    LinkNode *node1 = (LinkNode*)malloc(sizeof(LinkNode));
    LinkNode *node2 = (LinkNode*)malloc(sizeof(LinkNode));
    LinkNode *node3 = (LinkNode*)malloc(sizeof(LinkNode));
    LinkNode *node4 = (LinkNode*)malloc(sizeof(LinkNode));
    Data el1 = NULL;
    Data el2 = NULL;
    Data el3 = NULL;
    Data el4 = NULL;
    
    list = createList();
    insert(list, node1);

    search(list, el1);
    
    int len;
    
    int a = 8;
    int b = 1;
    int c = -5;
    int d = 100;

    el1 = &a;
    el2 = &b;
    el3 = &c;
    el4 = &d;

    
    node1->content = el1;
    node2->content = el2;
    node3->content = el3;
    node4->content = el4;
    
    len = lengthL(list);
        printf("ddd");
    printf("length of linkedlist: %d\n", len);
    printf("ddd");
        printf("ddd");
    insert(list, node1);
    printf("ddd");
    len = lengthL(list);
    printf("length of linkedlist: %d\n", len);
    
    insert(list, node2);
    len = lengthL(list);
    printf("length of linkedlist: %d\n", len);
    
    insert(list, node3);
    len = lengthL(list);
    printf("length of linkedlist: %d\n", len);
    
    insert(list, node4);
    len = lengthL(list);
    printf("length of linkedlist: %d\n", len);
    
    LinkNode *s1;
    s1 = search(list, el3);
    
    printData(s1->content);
    
    delete(list, s1);
    
    len = lengthL(list);
    printf("length of linkedlist: %d\n", len);
    
    s1 = search(list, el3);
    if (s1 != NULL) {
        printData(s1->content);
    } else {
        printf("Searched element is NULL.\n");
    }

    
    delete(list, s1);

}

void testArrayQueue()
{
    array_queue *queue = initQueue(MAXIMUM_QUEUE);
    int size = 65536;
    srand((u_int32_t)time(NULL));
    clock_t start = clock();

    for (int i = 0; i < size; i++) {
        int* el = (int*)malloc(sizeof(Data));
        *el = rand();
        addToQueue(queue, el);
    }
    clock_t mid = clock();
    quickSort(queue, 0, queue->length-1);
    clock_t mid2 = clock();

    for (int i = 0; i < size; i++) {
        getFirstFromQueue(queue);
    }
    clock_t end = clock();
    float inserttime = (float)(mid - start) / CLOCKS_PER_SEC;
    float sortTime = (float)(mid2 - mid) / CLOCKS_PER_SEC;
    float seconds = (float)(end - mid2) / CLOCKS_PER_SEC;
    printf("ArrayQueue of size %d:\n Execution time of insert %f, sort %f, extract %f, total %f\n",size, inserttime, sortTime, seconds, inserttime+sortTime+seconds);
    //printQueueInts(queue);
    
    array_queue *queueThread = initQueue(MAXIMUM_QUEUE);
    srand((u_int32_t)time(NULL));
    start = clock();
    
    for (int i = 0; i < size; i++) {
        int* el = (int*)malloc(sizeof(Data));
        *el = rand();
        addToQueue(queueThread, el);
    }
    mid = clock();
    quickSort_threadsStart(queueThread, 0, queueThread->length-1);
    mid2 = clock();
    
    for (int i = 0; i < size; i++) {
        getFirstFromQueue(queueThread);
    }
    end = clock();
    inserttime = (float)(mid - start) / CLOCKS_PER_SEC;
    sortTime = (float)(mid2 - mid) / CLOCKS_PER_SEC;
    seconds = (float)(end - mid2) / CLOCKS_PER_SEC;
    printf("ArrayQueue of size %d, using threads.:\n Execution time of insert %f, sort %f, extract %f, total %f\n",size, inserttime, sortTime, seconds, inserttime+sortTime+seconds);
    //printQueueInts(queue);
    
}

void testHeap()
{
    Heap *heap = init_heap();
    int size = 65536;
    srand((u_int32_t)time(NULL));
    
    clock_t start = clock();
    for (int i = 0; i < size; i++)
    {
        int* el = (int*)malloc(sizeof(Data));
        *el = rand();
        max_heap_insert(heap, el);
    }
    clock_t mid = clock();
    
    for (int i = 0; i < size; i++)
    {
        Data el = heap_extract_max(heap);
        free(el);
    }
    clock_t end = clock();
    float insertTime =(float)(mid - start) / CLOCKS_PER_SEC;
    float seconds = (float)(end - mid) / CLOCKS_PER_SEC;
    printf("Heap of size %d:\n Execution time of insert %f, extract %f, total %f\n"
           , size, insertTime, seconds, insertTime+seconds);
}

void testFibHeap()
{
    fib_heap* fibheap = fibHeap_make_heap();

    int size = 65536;
    
    srand((u_int32_t)time(NULL));
    clock_t start = clock();
    for (int i = 0; i < size; i++)
    {
        fib_heap_node *node = (fib_heap_node*)malloc(sizeof(fib_heap_node));
        node->key = (rand() % 99) + 1;
        fibHeap_insert(fibheap, node);
    }
    clock_t mid = clock();
    float buildingAr = 0;

    for (int i = 0; i < size; i++)
    {
        float time = fibHeap_extract_minimum(fibheap);
        //free(node);
        buildingAr = buildingAr + time;
    }
    clock_t end = clock();
    float insertTime =(float)(mid - start) / CLOCKS_PER_SEC;
    float seconds = (float)(end - mid) / CLOCKS_PER_SEC;
    printf("Fibheap of size %d:\n Execution time of insert %f, extract %f (building array time: %f), total %f\n Percent extracting-time spent building the array: %f\n"
           , size, insertTime, seconds, buildingAr, insertTime+seconds, buildingAr/seconds*100);
}

void testProtoVEBTree()
{
    int unisize = 65536;
    proto_vEBTree_struct *tree = proto_vEBTree_init(unisize,1);
    int size = 65536;
    srand((u_int32_t)time(NULL));
    
    clock_t start = clock();
    
    for (int i=0; i < size; i++)
    {
        proto_vEBTree_insert(tree, (rand() % size));
    }
    clock_t mid = clock();
    for (int i=0; i < size; i++)
    {
        proto_vEBTree_extract_minimum(tree);
    }
    clock_t end = clock();
    float inserttime = (float)(mid-start)/CLOCKS_PER_SEC;
    float extracttime = (float)(end-mid)/CLOCKS_PER_SEC;
    printf("Proto_vEBTrees of size %d and with unisize of %d:\n Execution time of insert %f, extract %f, total %f\n", size, unisize, inserttime, extracttime, inserttime+extracttime);
}

void testVEBTree()
{
    int unisize = 16;
    vEBTree *tree = vEBTree_init(unisize,1);
   /* int min;
    vEBTree_insert(tree, 2);
    vEBTree_insert(tree, 3);
    vEBTree_insert(tree, 4);
    vEBTree_insert(tree, 5);
    vEBTree_insert(tree, 7);
    vEBTree_insert(tree, 14);
    vEBTree_insert(tree, 15);
    vEBTree_printContent(&tree, 0);
    min = vEBTree_extract_minimum(tree);
    printf("min = %d\n",min);
    //vEBTree_printContent(&tree, 0);
    min = vEBTree_extract_minimum(tree);
    printf("min = %d\n",min);
    //vEBTree_printContent(&tree, 0);
    min = vEBTree_extract_minimum(tree);
    printf("min = %d\n",min);
    //vEBTree_printContent(&tree, 0);
    min = vEBTree_extract_minimum(tree);
    printf("min = %d\n",min);
    //vEBTree_printContent(&tree, 0);
    min = vEBTree_extract_minimum(tree);
    printf("min = %d\n",min);
    min = vEBTree_extract_minimum(tree);
    printf("min = %d\n",min);
    min = vEBTree_extract_minimum(tree);
    printf("min = %d\n",min);
    vEBTree_printContent(&tree, 0);
    */
    
    
    int size = 16;
    srand((u_int32_t)time(NULL));
    
    clock_t start = clock();
    
    for (int i=0; i < size; i++)
    {
        int a = rand() % size;
        printf("- Inserting %d\n",i);
        vEBTree_insert(tree, i);
    }
    clock_t mid = clock();
    printf("Now is extracting\n");
    for (int i=0; i < size; i++)
    {
        int b = vEBTree_extract_minimum(tree);
        printf("Extracted %d\n",b);
    }
    clock_t end = clock();
    float inserttime = (float)(mid-start)/CLOCKS_PER_SEC;
    float extracttime = (float)(end-mid)/CLOCKS_PER_SEC;
    printf("vEBTrees of size %d and with unisize of %d:\n Execution time of insert %f, extract %f, total %f\n", size, unisize, inserttime, extracttime, inserttime+extracttime);
     
}

int main()
{
    printf("Hello, World!\n");

    //testArrayQueue();
    //testHeap();
    //testFibHeap();
    //testProtoVEBTree();
    testVEBTree();
    
    
    printf("Hello, World!\n");
    return 0;
}
