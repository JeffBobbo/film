#include "csv.h"

#include <stdio.h>
#include <string.h>

#include "alloc.h"
#include "llist.h"

static char DELIMITER = ',';

LinkedList** csv_read(const char* const filename, size_t* const c)
{
  *c = 0;
  FILE* f = fopen(filename, "r");
  if (!f)
    return NULL;

  char line[512];
  size_t lineCount = 0;
  while (fgets(line, sizeof(line), f))
    ++lineCount;

  LinkedList** csv = (LinkedList**)malloc(sizeof(LinkedList*) * lineCount);
  if (!csv)
    return NULL;

  rewind(f); // go back to the beginning
  while (fgets(line, sizeof(line), f))
  {
    LinkedList* entry = ll_new();
    size_t p = 0;
    while (p < strlen(line))
    {
      if (line[p] == DELIMITER || line[p] == '\n')
      {
        ++p;
      }
      else
      {
        size_t len = 0;
        if (line[p] == '"')
        {
          ++p;
          size_t end = p;
          while (line[end] != '"')
            ++end;
          len = end - p;
        }
        else
        {
          size_t end = p;
          while (line[end] != DELIMITER && line[end] != '\n')
            ++end;
          len = end - p;
        }
        char* str = mt_malloc(sizeof(char) * (len + 1));
        memcpy(str, line+p, sizeof(char) * len);
        str[len] = '\0';
        ll_push_back(entry, str);
        p += len + 1;
      }
    }
    if (ll_size(entry))
      csv[(*c)++] = entry;
  }
  fclose(f);
  return csv;
}
