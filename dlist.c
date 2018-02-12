/******************************************************************************
 * NAME:	    dlist.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    A test file for the custom implementation of
 *		    the doubly-linked list in dlinkedlist.h. NOTE: Each of the
 *		    tests is set up so that while removing, numbers should be
 *		    printed out in the same order as when inserting, regardless
 *		    of the order that they are stored in the list.
 *
 * CREATED:	    03/31/2017
 *
 * LAST EDITED:	    02/12/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONFIG_DEBUG_DLIST
#include <time.h>
#endif /* CONFIG_DEBUG_DLIST */

#include "dlist.h"

/******************************************************************************
 * LOCAL PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG_DLIST
static inline void error_exit(char *);
static void test_head_next(dlist *, int *);
static void test_tail_next(dlist *, int *);
static void test_head_prev(dlist *, int *);
static void test_tail_prev(dlist *, int *);
#endif /* CONFIG_DEBUG_DLIST */

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    dlist_create
 *
 * DESCRIPTION:	    Initializes a dlist and returns a pointer to it.
 *
 * ARGUMENTS:	    dlist: (dlist *) -- the list to be operated on.
 *		    destroy: (void (*)(void *)) -- function pointer for user-
 *			     defined function to free memory associated with
 *			     data held in the list.
 *
 * RETURN:	    (dlist *) -- pointer to the new struct, or NULL if there
 *		    was an error.
 *
 * NOTES:	    O(1)
 ***/
dlist * dlist_create(void (*destroy)(void *))
{
  dlist * list = NULL;
  if ((list = malloc(sizeof(dlist))) == NULL)
    return NULL;

  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

/******************************************************************************
 * FUNCTION:	    dlist_insnxt
 *
 * DESCRIPTION:	    Inserts a new node after the node specified.
 *
 * ARGUMENTS:	    dlist: (dlist *) -- the list to be operated on.
 *		    node: (dlistelmt *) -- the reference node.
 *		    data: (const void *) -- the data to populate the new node.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int dlist_insnxt(dlist * dlist, dlistelmt * node, const void * data)
{
  dlistelmt * new;

  if (node == NULL && !dlist_isempty(dlist))
    return -1;

  /* Perform null check and allocate new memory */
  if ((new = (dlistelmt *)malloc(sizeof(dlistelmt))) == NULL)
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

/******************************************************************************
 * FUNCTION:	    dlist_insprev
 *
 * DESCRIPTION:	    Inserts a new node before the node specified.
 *
 * ARGUMENTS:	    dlist: (dlist *) -- the list to be operated on.
 *		    node: (dlistelmt *) -- the reference node.
 *		    data: (const void *) -- the data to populate the new node.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int dlist_insprev(dlist * dlist, dlistelmt * node, const void * data)
{
  dlistelmt * new;
  
  /* Once again, do not allow a null pointer for node if the list is not
   * empty.
   */
  if (node == NULL && !dlist_isempty(dlist))
    return -1;

  if ((new = (dlistelmt *)malloc(sizeof(dlistelmt))) == NULL)
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

/******************************************************************************
 * FUNCTION:	    dlist_remove
 *
 * DESCRIPTION:	    Removes the node provided.
 *
 * ARGUMENTS:	    dlist: (dlist *) -- the list to be operated on.
 *		    node: (dlistelmt *) -- the node to be removed.
 *		    data: (const void *) -- data from the node is placed here.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int dlist_remove(dlist * dlist, dlistelmt * node, void ** data)
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

/******************************************************************************
 * FUNCTION:	    dlist_destroy
 *
 * DESCRIPTION:	    Removes all nodes in the list and sets all memory in the
 *		    structure to 0. If destroy is set to NULL, does not
 *		    destroy the data held within the nodes.
 *
 * ARGUMENTS:	    list: (dlist *) -- the list to be operated on.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(n)
 ***/
int dlist_destroy(dlist ** list)
{
  void * data;
  if ((*list)->destroy == NULL)
    return -1;

  while (!dlist_isempty(*list)) {
    if (dlist_remove(*list, dlist_tail(*list), (void **)&data) == 0)
      if ((*list)->destroy != NULL)
	(*list)->destroy(data);
  }

  free(*list);
  *list = NULL;
  return 0;
}

/******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG_DLIST
int main(int argc, char * argv[])
{

  /* TODO: Refactor testing
   */

  dlist * list = NULL;
  int * pNum = NULL;

  srand((unsigned)time(NULL));

  test_head_next(list, pNum);
  test_tail_next(list, pNum);
  test_head_prev(list, pNum);
  test_tail_prev(list, pNum);

  if (list != NULL)
    error_exit("List was not destroyed correctly!");
}
#endif /* CONFIG_DEBUG_DLIST */

/******************************************************************************
 * LOCAL FUNCTIONS
 ***/

#ifdef CONFIG_DEBUG_DLIST
static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

static void test_head_next(dlist * list, int * pNum)
{
  /* ==================================================
   * HEAD TEST, INSNXT
   * ================================================== */
  printf("Head test, insnxt\n");
  printf("==== Inserting ====\n");
  if ((list = dlist_create(free)) == NULL)
    error_exit("Could not create list!");
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
    dlist_remove(list, dlist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }
  printf("\n");
  dlist_destroy(&list);
}

static void test_tail_next(dlist * list, int * pNum)
{
  /* ==================================================
   * TAIL TEST, INSNXT
   * ================================================== */
  printf("Tail test, insnxt\n");
  printf("==== Inserting ====\n");
  if ((list = dlist_create(free)) == NULL)
    error_exit("Could not create list!");
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
    dlist_remove(list, dlist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }
  printf("\n");
  dlist_destroy(&list);
}

static void test_head_prev(dlist * list, int * pNum)
{
  /* ==================================================
   * HEAD TEST, INSPREV
   * ================================================== */
  printf("Head test, insprev\n");
  if ((list = dlist_create(free)) == NULL)
    error_exit("Could not create list!");
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
    dlist_remove(list, dlist_tail(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }
  printf("\n");
  dlist_destroy(&list);
}

static void test_tail_prev(dlist * list, int * pNum)
{
  /* ==================================================
   * TAIL TEST, INSPREV
   * ================================================== */
  printf("Tail test, insprev\n");
  if ((list = dlist_create(free)) == NULL)
    error_exit("Could not create list!");
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
    dlist_remove(list, dlist_tail(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }
  printf("\n");
  dlist_destroy(&list);
}
#endif /* CONFIG_DEBUG_DLIST */

/*****************************************************************************/
