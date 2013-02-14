#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Definitions.h"

/**
 An implementation of double linked list.
 It is not ordered by default and does very little to no
 memory management for the user.
 There can be no doublets of keys.
 */

typedef struct LinkNode_ {
  Data content;
  struct LinkNode_ *prev;
  struct LinkNode_ *next;
} LinkNode;

typedef struct LinkedList_ {
  struct LinkNode_ *header;
} LinkedList;

/**
   Returns the length of a given list.
 */
int lengthL(LinkedList *list);

/**
   Returns a node containing the given key.
   Returns NULL if none is found.
 */
LinkNode* search(LinkedList *list, Data key);

/**
   Insert a new node to the list.
 */
void insert(LinkedList *list, LinkNode *node);

/**
   Delete a given node from the list, if it exists.
 */
void delete(LinkedList *list, LinkNode *node);

/**
 Initialises an empty list.
 */
LinkedList* createList();


/* Only works for ordered linkedlist
   fun order (list, (desc|asc)) ?
LinkNode* minimum(LinkListed *list);

LinkNode* maximum(LinkListed *list);

LinkNode* successor(LinkListed *list, LinkNode *node);

LinkNode* predecessor(LinkListed *list, LinkNode *node);
*/
#endif /* LINKED_LIST_H */
