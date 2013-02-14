//
//  main.c
//  DataStructures
//
//  Created by Arni Asgeirsson on 12/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "LinkedList.h"
#include "ArrayQueue.h"

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
    array_queue *queue = NULL;
    int* el1 = (int*)malloc(sizeof(int));
    Data el2 = NULL;
    Data el3 = NULL;
    Data el4 = NULL;
    Data el5 = NULL;
    Data el6 = NULL;
    Data el7 = NULL;
    Data el8 = NULL;
    Data el9 = NULL;
    Data el10 = NULL;
    Data g = (Data)malloc(sizeof(Data));
    int a1 = 11111;
    int a2 = 5;
    int a3 = 2;
    int a4 = -1;
    int a5 = 10;
    int a6 = 220;
    int a7 = 2;
    int a8 = 1;
    int a9 = 7;
    int a10 = 8;
/*
    int len = -1;
    int i = 0;
*/
    *el1 = a1;
    el2 = &a2;
    el3 = &a3;
    el4 = &a4;
    el5 = &a5;
    el6 = &a6;
    el7 = &a7;
    el8 = &a8;
    el9 = &a9;
    el10 = &a10;

    queue = initQueue(MAXIMUM_QUEUE);
    addToQueue(queue, a1);
    addToQueue(queue, a2);
    addToQueue(queue, a3);
    addToQueue(queue, a4);
    addToQueue(queue, a5);
    addToQueue(queue, a6);
    addToQueue(queue, a7);
    addToQueue(queue, a8);
    addToQueue(queue, a9);
    addToQueue(queue, a10);

    //quickSort(queue, 0, queue->length-1);
    //int gg = getFirstFromQueue(queue);


    
    //printf("g = %d\n", gg);
    
    /*
    printf("len: %d\n", len);
    printf("el1: %d\n", *((int*)(el5)));
    printf("queue[%d] = %d\n", i, *(int*)(*(queue->array[i])));
    */
    
    printQueueInts(queue);
}

int main()
{
    printf("Hello, World!\n");

    testArrayQueue();
    /*testLinkedList();*/
    /*testQueue();*/
    
    
    printf("Hello, World!\n");
    return 0;
}
