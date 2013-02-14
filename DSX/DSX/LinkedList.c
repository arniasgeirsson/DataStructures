
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/**
   Returns the length of a given list.
*/
int lengthL(LinkedList *list)
{
    if (list == NULL) {
        printf("LengthL: List cannot be NULL.\n");
        return 0;
    }
    
    int len = 0;
    
    LinkNode *node = (*list).header;
    
    while (node != NULL) {
        len++;
        node = (*node).next;
    }
    
    return len;
}

LinkedList* createList()
{
    return (LinkedList*)malloc(sizeof(LinkedList));
}

/**
 Returns the first occurance of a node
 containing the given key.
 Returns NULL if none is found.
*/
LinkNode* search(LinkedList *list, Data key)
{
    if (list == NULL) {
        printf("Search: List cannot be NULL.\n");
        return NULL;
    }
    if (list->header == NULL)
    {
        printf("Search: List is empty.\n");
        return NULL;
    }
    
    if (key == NULL) {
        printf("Search: The given Data is NULL.\n");
        return NULL;
    }
    
    LinkNode *node = NULL;
    LinkNode *first = list->header;
    
    int notFound = 1;
    
    while (notFound && first != NULL) {
        if (first->content == key) {
            notFound = 0;
            node = first;
        }
        first = first->next;
    }
    
    return node;
}


/**
   Insert a new node to the list.
*/
void insert(LinkedList *list, LinkNode *node)
{
    /* Pass in comparingsons function? */ 
    if (list == NULL) {
        printf("Insert: List cannot be NULL.\n");
        return;
    }
    
    if (node == NULL) {
        printf("Insert: Inserting node is NULL.\n");
        return;
    }
    
    if (list->header == NULL)
    {
        list->header = node;
        return;
    }
    
    if (search(list, node->content) != NULL) {
        printf("Insert: Element already exists, cannot be inserted.\n");
        return;
    }
    
    LinkNode *lNode = list->header;
    
    while (lNode->next != NULL) {
        printf("sad");
        lNode = lNode->next;
    }
    lNode->next = node;
    node->prev = lNode;
}

/**
   Delete a given node from the list, if it exists.
*/
void delete(LinkedList *list, LinkNode *node)
{
    if (list == NULL) {
        printf("Delete: List cannot be NULL.\n");
        return;
    }
    if (list->header == NULL)
    {
        printf("Delete: List is empty.\n");
        return ;
    }
    if (node == NULL) {
        printf("Delete: Deleting node is NULL.\n");
        return;
    }
    
    if (node->prev == NULL) {
        /* Is first element */
        list->header = node->next;
        return;
    }
    if (node->next == NULL) {
        /* Is the last element */
        node->prev->next = NULL;
        return;
    }
    
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

/* Only works for ordered linkedlist
   fun order (list, (desc|asc)) ?
LinkNode* minimum(LinkListed *list);
LinkNode* maximum(LinkListed *list);
LinkNode* successor(LinkListed *list, LinkNode *node);
LinkNode* predecessor(LinkListed *list, LinkNode *node);
*/
