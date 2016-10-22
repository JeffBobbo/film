#include "alloc.h"
#include "llist.h"

#include <stdio.h>
#include <stdint.h>

void runMemTest()
{
  char* p = mt_malloc(sizeof(char) * 5);
  char* q = mt_malloc(sizeof(char) * 6);
  p[5] = 5;
  //mt_free(p); // should emit message
  //mt_free(q); // should be fine

  p = mt_malloc(sizeof(char) * 20);
  q[0] = 'H';
}

void llTest()
{
  LinkedList* ll = ll_new();
  printf("List size is %zu\n", ll_size(ll));
  for (int i = 0; i < 10; ++i)
  {
    int* p = mt_malloc(sizeof(int));
    *p = 1 << i;
    ll_push_front(ll, p);
  }
  printf("List size is %zu\n", ll_size(ll));

  LinkedIterator* it = mt_malloc(16);
  for (int* i = (int*)ll_it_begin(it, ll); i; i = (int*)ll_it_next(it))
    printf("%i\n", *i);
  printf("And backwards...\n");
  for (int* i = (int*)ll_it_rbegin(it, ll); i; i = (int*)ll_it_rnext(it))
    printf("%i\n", *i);
  mt_free(it);

  ll_delete(ll);
}

int main()
{
  //runMemTest();
  llTest();
}
