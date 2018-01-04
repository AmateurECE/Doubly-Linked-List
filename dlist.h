/******************************************************************************
 * NAME:	    dlinkedlist.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file for the implementation of a doubly-linked-list.
 *
 * CREATED:	    03/31/2017
 *
 * LAST EDITED:	    01/03/2018
 ***/

#ifndef __ET_DLINKEDLIST_H__
#define __ET_DLINKEDLIST_H__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _dlistelmt_ {

  void * data;
  struct _dlistelmt_ * prev;
  struct _dlistelmt_ * next;

} dlistelmt;

typedef struct _dlist_ {

  int size;
  void (*destroy)(void * data);
  dlistelmt * head;
  dlistelmt * tail;

} dlist;

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define dlist_size(dlist) ((dlist)->size)
#define dlist_head(dlist) ((dlist)->head)
#define dlist_tail(dlist) ((dlist)->tail)
#define dlist_prev(node) ((node)->prev)
#define dlist_data(node) ((node)->data)
#define dlist_next(node) ((node)->next)

#define dlist_isempty(dlist) ((dlist)->size == 0 ? 1 : 0)
#define dlist_ishead(dlist, node) ((dlist)->head == node ? 1 : 0)
#define dlist_istail(dlist, node) ((dlist)->tail == node ? 1 : 0)

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern dlist * dlist_create(void (*destroy)(void *));
extern int dlist_insnxt(dlist * list, dlistelmt * elmt, const void * data);
extern int dlist_insprev(dlist * list, dlistelmt * elmt, const void * data);
extern int dlist_remove(dlist * list, dlistelmt * elmt, void ** data);
extern int dlist_destroy(dlist ** list);

/* TODO: Implement dlist_traverse
 */

#endif /* __ET_DLINKEDLIST_H__ */

/*****************************************************************************/
