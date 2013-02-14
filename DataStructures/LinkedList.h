#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef void* Data;

typedef struct LinkNode_ {
  Data content;
  LinkNode *prev;
  LinkNode *next;
} LinkNode;

typedef struct LinkedList_ {
  LinkNode *header;
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

/* Only works for ordered linkedlist
   fun order (list, (desc|asc)) ?
LinkNode* minimum(LinkListed *list);

LinkNode* maximum(LinkListed *list);

LinkNode* successor(LinkListed *list, LinkNode *node);

LinkNode* predecessor(LinkListed *list, LinkNode *node);
*/
#endif LINKED_LIST_H
