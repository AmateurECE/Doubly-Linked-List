/*******************************************************************************
 * TITLE:	    dlinkedlist.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file for the implementation of a doubly-linked-list.
 *
 * CREATED: 03/31/17
 *
 * LAST EDITED: 01/02/2018
 ***/

#ifndef __ET_DLINKEDLIST_H__
#define __ET_DLINKEDLIST_H__

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

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

/*******************************************************************************
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

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern void dlist_init(DList *, void (*)(void *));
extern int dlist_insnxt(DList *, DListElm *, const void *);
extern int dlist_insprev(DList *, DListElm *, const void *);
extern int dlist_rem(DList *, DListElm *, void **);
extern int dlist_dest(DList *);

/* TODO: Implement dlist_traverse
 */

#endif /* __ET_DLINKEDLIST_H__ */

/******************************************************************************/
