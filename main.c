#include "alloc.h"

#include <stdio.h>
#include <stdint.h>

void runMemTest()
{
  uint32_t* p = mt_malloc(5, sizeof(uint32_t));
  p[5] = 5;
  mt_free(p); // should emit message

  p = mt_malloc(5, sizeof(char));
  size_t leaked = check();
  printf("%u\n", leaked); // should print 5
}

int main()
{
  runMemTest();
}
