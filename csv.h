#ifndef CSV_H_INCLUDE
#define CSV_H_INCLUDE

#include "llist.h"

typedef struct csv_t
{
  LinkedList* data;
} CSV;


CSV* csv_read(const char* const filename);
void csv_free(CSV* const csv);

#endif
