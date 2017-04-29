/*
 * TITLE: dlinkedlist.h
 * AUTHOR: Ethan D. Twardy
 * CREATED: 03/31/17
 * LAST EDITED: 03/31/17
 *
 * DESCRIPTION: A custom implementation of a
 * Doubly-linked list. Woot.
 */

#ifndef __ET_DLINKEDLIST__
#define __ET_DLINKEDLIST__

#include <stdlib.h>
#include <string.h>

/************* TYPE DEFINITIONS *************/
/********************************************/

typedef struct _DListElm_ {

  void * data;
  struct _DListElm_ * prev;
  struct _DListElm_ * next;

} DListElm;

typedef struct _dlist_ {

  int size;
  void (*destroy)(void * data);
  DListElm * head;
  DListElm * tail;

} DList;

/************* MACRO DEFINITIONS ************/
/********************************************/

#define dlist_size(dlist) ((dlist)->size)
#define dlist_head(dlist) ((dlist)->head)
#define dlist_tail(dlist) ((dlist)->tail)
#define dlist_prev(node) ((node)->prev)
#define dlist_data(node) ((node)->data)
#define dlist_next(node) ((node)->next)

#define dlist_isempty(dlist) ((dlist)->size == 0 ? 1 : 0)
#define dlist_ishead(dlist, node) ((dlist)->head == node ? 1 : 0)
#define dlist_istail(dlist, node) ((dlist)->tail == node ? 1 : 0)

/************* PUBLIC INTERFACE ************/
/*******************************************/

// FUNCTION: dlist_init O(1) -- initializes a list pointer
// PARAMETERS: dlist: DList* -- the list to be operated on
//             destroy: function* -- the user-defined function for freeing the data
// RETURN: void
void dlist_init(DList * dlist, void (*destroy)(void * data))
{
  dlist->size = 0;
  dlist->destroy = destroy;
  dlist->head = NULL;
  dlist->tail = NULL;
  return;
}

// FUNCTION: dlist_insnxt O(1) -- inserts a new node after the reference node
// PARAMETERS: dlist: DList* -- the list to be operated on.
//             node: DListElm* -- reference node. The new node is inserted after this node.
//             data: const void* -- data to populate the node
// RETURN: int -- -1 for failure, 0 for success.
int dlist_insnxt(DList * dlist, DListElm * node, const void * data)
{
  DListElm * new;

  if (node == NULL && !dlist_isempty(dlist))
    return -1;

  // Perform null check and allocate new memory
  if ((new = (DListElm *)malloc(sizeof(DListElm))) == NULL)
    return -1;

  new->data = (void *)data;

  if (dlist_isempty(dlist)) {
    // Handle insertion when the list is empty
    
    dlist->head = new;
    dlist->head->prev = NULL;
    dlist->head->next = NULL;
    dlist->tail = new;

  } else {
    // Handle insertion when the list is not empty
    new->next = node->next;
    new->prev = node;

    if (node->next == NULL)
      dlist->tail = new;
    else
      node->next->prev = new;

    node->next = new;
  }
  
  dlist->size++;
  return 0;
}

// FUNCTION: dlist_insprev O(1) -- inserts a new node previous to the reference node
// PARAMETERS: dlist: DList* -- the list to be operated on.
//             node: DListElm* -- the reference node. New node is inserted after this node.
//             data: const void* -- data to populate the node.
// RETURN: int -- -1 on failure, 0 on success.
int dlist_insprev(DList * dlist, DListElm * node, const void * data)
{
  DListElm * new;
  
  // Once again, do not allow a null pointer for node if the list is not empty.
  if (node == NULL && !dlist_isempty(dlist))
    return -1;

  if ((new = (DListElm *)malloc(sizeof(DListElm))) == NULL)
    return -1;

  new->data = (void *)data;

  if (dlist_isempty(dlist)) {
    // Handle insertion when the list is empty.

    dlist->head = new;
    dlist->head->prev = NULL;
    dlist->head->next = NULL;
    dlist->tail = new;

  } else {
    // Handle insertion when the list is not empty.

    new->next = node;
    new->prev = node->prev;

    if (node->prev == NULL)
      dlist->head = new;
    else
      node->prev->next = new;

    node->prev = new;

  }
  
  dlist->size++;
  return 0;
}

// FUNCTION: dlist_rem O(1) -- removes the node provided to the function.
// PARAMETERS: dlist: DList* -- the list to be operated on.
//             node: DListElm* -- the node to be removed.
//             data: void** -- the data (void*) from node is placed at this location.
// RETURN: int -- -1 on failure, 0 on success.
int dlist_rem(DList * dlist, DListElm * node, void ** data)
{
  if (node == NULL || dlist_isempty(dlist))
    return -1;

  *data = node->data;

  if (dlist_ishead(dlist, node)) {
    // Handle removal from the head of the list
    dlist->head = node->next;
    
    if (dlist->head == NULL)
      dlist->tail = NULL;
    else
      node->next->prev = NULL;

  } else {
    // Handle removal from somewhere else in the list
    node->prev->next = node->next;
    
    if (node->next == NULL)
      dlist->tail = node->prev;
    else
      node->next->prev = node->prev;

  }

  free(node);
  dlist->size--;
  return 0;
}

// FUNCTION: dlist_dest O(n) -- removes all nodes and sets all bytes to 0.
// PARAMETERS: dlist: DList* -- the list to be operated on.
// RETURN: int -- -1 on failure, 0 on success.
int dlist_dest(DList * dlist)
{
  void * data;
  if (dlist->destroy == NULL)
    return -1;

  while (!dlist_isempty(dlist)) {
    if (dlist_rem(dlist, dlist_tail(dlist), (void **)&data) == 0)
      dlist->destroy(data);
  }

  memset(dlist, 0, sizeof(DList));
  return 0;
}

#endif // __ET_DLINKEDLIST__
