#include "alloc.h"

#include <stdio.h>
#include <stdint.h>

void runMemTest()
{
  char* p = mt_malloc(5, sizeof(char));
  p[5] = 5;
  mt_free(p); // should emit message

  p = mt_malloc(5, sizeof(char));
}

int main()
{
  runMemTest();
}
