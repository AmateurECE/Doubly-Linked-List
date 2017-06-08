/*******************************************************************************
 * NAME:	    dlinkedlist.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    A test file for the custom implementation of
 *		    the doubly-linked list in dlinkedlist.h. NOTE: Each of the
 *		    tests is set up so that while removing, numbers should be
 *		    printed out in the same order as when inserting, regardless
 *		    of the order that they are stored in the list.
 *
 * CREATED:	    03/31/17
 *
 * LAST EDITED:	    06/06/17
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONFIG_DEBUG_DLIST
#include <time.h>
#endif /* CONFIG_DEBUG_DLIST */

#include "dlinkedlist.h"

/*******************************************************************************
 * LOCAL PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG_DLIST
static inline void error_exit(char *);
static void test_head_next(DList *, int *);
static void test_tail_next(DList *, int *);
static void test_head_prev(DList *, int *);
static void test_tail_prev(DList *, int *);
#endif /* CONFIG_DEBUG_DLIST */

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    dlist_init
 *
 * DESCRIPTION:	    Initializes a DList pointer.
 *
 * ARGUMENTS:	    dlist: (DList *) -- the list to be operated on.
 *		    destroy: (void (*)(void *)) -- function pointer for user-
 *			     defined function to free memory associated with
 *			     data held in the list.
 *
 * RETURN:	    void
 *
 * NOTES:	    O(1)
 ***/
void dlist_init(DList * dlist, void (*destroy)(void * data))
{
  dlist->size = 0;
  dlist->destroy = destroy;
  dlist->head = NULL;
  dlist->tail = NULL;
  return;
}

/*******************************************************************************
 * FUNCTION:	    dlist_insnxt
 *
 * DESCRIPTION:	    Inserts a new node after the node specified.
 *
 * ARGUMENTS:	    dlist: (DList *) -- the list to be operated on.
 *		    node: (DListElm *) -- the reference node.
 *		    data: (const void *) -- the data to populate the new node.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int dlist_insnxt(DList * dlist, DListElm * node, const void * data)
{
  DListElm * new;

  if (node == NULL && !dlist_isempty(dlist))
    return -1;

  /* Perform null check and allocate new memory */
  if ((new = (DListElm *)malloc(sizeof(DListElm))) == NULL)
    return -1;

  new->data = (void *)data;

  if (dlist_isempty(dlist)) {
    /* Handle insertion when the list is empty */
    
    dlist->head = new;
    dlist->head->prev = NULL;
    dlist->head->next = NULL;
    dlist->tail = new;

  } else {
    /* Handle insertion when the list is not empty */
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

/*******************************************************************************
 * FUNCTION:	    dlist_insprev
 *
 * DESCRIPTION:	    Inserts a new node before the node specified.
 *
 * ARGUMENTS:	    dlist: (DList *) -- the list to be operated on.
 *		    node: (DListElm *) -- the reference node.
 *		    data: (const void *) -- the data to populate the new node.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int dlist_insprev(DList * dlist, DListElm * node, const void * data)
{
  DListElm * new;
  
  /* Once again, do not allow a null pointer for node if the list is not empty. */
  if (node == NULL && !dlist_isempty(dlist))
    return -1;

  if ((new = (DListElm *)malloc(sizeof(DListElm))) == NULL)
    return -1;

  new->data = (void *)data;

  if (dlist_isempty(dlist)) {
    /* Handle insertion when the list is empty. */

    dlist->head = new;
    dlist->head->prev = NULL;
    dlist->head->next = NULL;
    dlist->tail = new;

  } else {
    /* Handle insertion when the list is not empty. */

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

/*******************************************************************************
 * FUNCTION:	    dlist_rem
 *
 * DESCRIPTION:	    Removes the node provided.
 *
 * ARGUMENTS:	    dlist: (DList *) -- the list to be operated on.
 *		    node: (DListElm *) -- the node to be removed.
 *		    data: (const void *) -- data from the node is placed here.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int dlist_rem(DList * dlist, DListElm * node, void ** data)
{
  if (node == NULL || dlist_isempty(dlist))
    return -1;

  *data = node->data;

  if (dlist_ishead(dlist, node)) {
    /* Handle removal from the head of the list */
    dlist->head = node->next;
    
    if (dlist->head == NULL)
      dlist->tail = NULL;
    else
      node->next->prev = NULL;

  } else {
    /* Handle removal from somewhere else in the list */
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

/*******************************************************************************
 * FUNCTION:	    dlist_dest
 *
 * DESCRIPTION:	    Removes all nodes in the list and sets all bytes in the list
 *		    structure to be 0. If destroy is set to NULL, does not
 *		    destroy the data held within the nodes.
 *
 * ARGUMENTS:	    dlist: (DList *) -- the list to be operated on.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(n)
 ***/
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

/*******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG_DLIST
int main(int argc, char * argv[])
{
  DList * list = NULL;
  int * pNum = NULL;

  if ((list = (DList *)malloc(sizeof(DList))) == NULL)
    error_exit("Could not allocate memory for DList!");

  srand((unsigned)time(NULL));

  test_head_next(list, pNum);

  test_tail_next(list, pNum);

  test_head_prev(list, pNum);

  test_tail_prev(list, pNum);

  free(list);
}
#endif /* CONFIG_DEBUG_DLIST */

/*******************************************************************************
 * LOCAL FUNCTIONS
 ***/

#ifdef CONFIG_DEBUG_DLIST
static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

static void test_head_next(DList * list, int * pNum)
{
  /* ==================================================
   * HEAD TEST, INSNXT
   * ================================================== */
  printf("Head test, insnxt\n");
  printf("==== Inserting ====\n");
  dlist_init(list, free);
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;
    printf("int %d @ %p", *pNum, pNum);
    if (dlist_insnxt(list, dlist_head(list), pNum) == -1)
      printf(" RETURNED -1");
    printf("\n");
  }

  /* ===== REMOVE FROM THE LIST ===== */

  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    /* FREE MEMORY HERE */
  }
  printf("\n");
  dlist_dest(list);
}

static void test_tail_next(DList * list, int * pNum)
{
  /* ==================================================
   * TAIL TEST, INSNXT
   * ================================================== */
  printf("Tail test, insnxt\n");
  printf("==== Inserting ====\n");
  dlist_init(list, free);
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;
    printf("int %d @ %p", *pNum, pNum);
    if (dlist_insnxt(list, dlist_tail(list), pNum) == -1)
      printf("RETURNED -1");
    printf("\n");
  }

  /* ===== REMOVE FROM THE LIST ===== */

  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    /* FREE MEMORY HERE */
  }
  printf("\n");
  dlist_dest(list);
}

static void test_head_prev(DList * list, int * pNum)
{
  /* ==================================================
   * HEAD TEST, INSPREV
   * ================================================== */
  printf("Head test, insprev\n");
  dlist_init(list, free);
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;
    printf("int %d @ %p", *pNum, pNum);
    if (dlist_insprev(list, dlist_head(list), pNum) == -1)
      printf("RETURNED -1");
    printf("\n");
  }

  /* ===== REMOVE FROM THE LIST ===== */
  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_tail(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    /* FREE MEMORY HERE */
  }
  printf("\n");
  dlist_dest(list);
}

static void test_tail_prev(DList * list, int * pNum)
{
  /* ==================================================
   * TAIL TEST, INSPREV
   * ================================================== */
  printf("Tail test, insprev\n");
  dlist_init(list, free);
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;
    printf("int %d @ %p", *pNum, pNum);
    if (dlist_insprev(list, dlist_tail(list), pNum) == -1)
      printf("RETURNED -1");
    printf("\n");
  }

  /* ===== REMOVE FROM THE LIST ===== */

  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_tail(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    /* FREE MEMORY HERE */
  }
  printf("\n");
  dlist_dest(list);
}
#endif /* CONFIG_DEBUG_DLIST */

/******************************************************************************/
