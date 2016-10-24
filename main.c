#include <stdio.h>
#include <stdint.h>

#include "alloc.h"
#include "llist.h"
#include "csv.h"

void runMemTest()
{
  char* p = mt_malloc(sizeof(char) * 5);
  char* q = mt_malloc(sizeof(char) * 6);
  p[5] = 5;
  mt_free(p); // should emit message
  mt_free(q); // should be fine

  p = mt_malloc(sizeof(char) * 20);
  p[0] = 'H';
}

bool comparison(const void* const a, const void* const b)
{
  return (*(int*)a > *(int*)b ? 1 : 0);
  //return (*(int*)a < *(int*)b ? -1 : (*(int*)a > *(int*)b ? 1 : 0));
}

void llTest()
{
  LinkedList* ll = ll_new();
  printf("List size is %zu\n", ll_size(ll));
  for (int i = 0; i < 10; ++i)
  {
    int* p = mt_malloc(sizeof(int));
    *p = rand() % 100;
    ll_push_back(ll, p);
  }
  printf("List size is %zu\n", ll_size(ll));

  LinkedIterator* it = mt_malloc(16);
  for (int* i = (int*)ll_it_begin(it, ll); i; i = (int*)ll_it_next(it))
    printf("%i\n", *i);
  ll_bsort(ll, &comparison);
  printf("And sorted...\n");
  for (int* i = (int*)ll_it_begin(it, ll); i; i = (int*)ll_it_next(it))
    printf("%i\n", *i);
  mt_free(it);

  ll_purge(ll);
}

int main()
{
  //runMemTest();
  //llTest();
  CSV* csv = csv_read("films.txt");

  if (!csv)
  {
    fprintf(stderr, "Failed to open file\n");
    return 1;
  }

  LinkedIterator* it = mt_malloc(16);
  LinkedList* row = (LinkedList*)ll_it_begin(it, csv->data);
  for (; row; row = (LinkedList*)ll_it_next(it))
  {
    printf("Entry:\n");
    LinkedIterator* it2 = mt_malloc(16);
    char* d = (char*)ll_it_begin(it2, row);
    for (; d; d = (char*)ll_it_next(it2))
      printf("\t%s\n", d);
    mt_free(it2);
    ll_clear(row);
  }
  mt_free(it);
  csv_free(csv);
}
