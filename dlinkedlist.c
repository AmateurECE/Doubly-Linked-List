/*
 * TITLE: dlinkedlist.c
 * AUTHOR: Ethan D. Twardy
 * CREATED: 03/31/17
 * LAST EDITED: 03/31/17
 *
 * DESCRIPTION: A test file for the custom implementation of
 * the doubly-linked list in dlinkedlist.h. NOTE: Each of the
 * tests is set up so that while removing, numbers should be
 * printed out in the same order as when inserting, regardless
 * of the order that they are stored in the list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dlinkedlist.h"

static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

void test_head_next(DList * list, int * pNum)
{
  // ==================================================
  // HEAD TEST, INSNXT
  // ==================================================
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

  // ===== REMOVE FROM THE LIST =====

  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    // FREE MEMORY HERE
  }
  printf("\n");
  dlist_dest(list);
}

void test_tail_next(DList * list, int * pNum)
{
  // ==================================================
  // TAIL TEST, INSNXT
  // ==================================================
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

  // ===== REMOVE FROM THE LIST =====

  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_head(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    // FREE MEMORY HERE
  }
  printf("\n");
  dlist_dest(list);
}

void test_head_prev(DList * list, int * pNum)
{
  // ==================================================
  // HEAD TEST, INSPREV
  // ==================================================
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

  // ===== REMOVE FROM THE LIST =====
  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_tail(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    // FREE MEMORY HERE
  }
  printf("\n");
  dlist_dest(list);
}

void test_tail_prev(DList * list, int * pNum)
{
  // ==================================================
  // TAIL TEST, INSPREV
  // ==================================================
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

  // ===== REMOVE FROM THE LIST =====

  printf("==== Removing =====\n");
  while (!dlist_isempty(list)) {
    dlist_rem(list, dlist_tail(list), (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    // FREE MEMORY HERE
  }
  printf("\n");
  dlist_dest(list);
}

int main(int argc, char * argv[])
{
  DList * list;
  int * pNum;

  if ((list = (DList *)malloc(sizeof(DList))) == NULL)
    error_exit("Could not allocate memory for DList!");

  srand((unsigned)time(NULL));

  test_head_next(list, pNum);

  test_tail_next(list, pNum);

  test_head_prev(list, pNum);

  test_tail_prev(list, pNum);

  free(list);
}
