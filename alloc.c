#include "alloc.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h> // memset
#include <stdlib.h> // atexit, [cm]alloc, free
#include <assert.h> // assert

#define MEMTEST

const char PADDING = 0;

static int registeredExit = 0;

typedef struct reserved_t
{
  void* base; // the base address of this reserved memory
  void* data; // where the data actually is
  void* dend; // where the data ends
  void* end; // the last piece of data in this bit of reserved memory
  size_t num; // how many elements is this memory for
  // n.b.: each individual element won't be padded, so corruption could occur here
  size_t size; // what's the size of each element
  struct reserved_t* next;
} Reserved;

Reserved* root = NULL;

Reserved* last()
{
  Reserved* node = root;
  while (1)
  {
    if (!node->next)
      break;
    node = node->next;
  }
  return node;
}

void* mt_malloc(const size_t n, const size_t sz)
{
#ifdef MEMTEST
  void* p = malloc(n*sz*2);
  if (p)
  {
    Reserved* r = (Reserved*)malloc(sizeof(Reserved));
    assert(r);
    r->base = p;
    r->data = ((n*sz) >> 1) + p;
    r->dend = r->data + sz * n;
    r->end = p + n*sz*2;
    r->num = n;
    r->size = sz;
    r->next = NULL;

    // set all the bytes except those in our data to be 0
    // this preserves the junk values we get
    // but allow us to test for under and overflows later
    memset(r->base, PADDING, r->data - r->base);
    memset(r->dend, PADDING, r->end - r->dend);

    // TODO: Fix bug here
    if (root)
      last()->next = r;
    else
      root = r;

    if (!registeredExit)
      registeredExit = !atexit(mt_check);

    return r->data;
  }
  return NULL;
#else
  return malloc(n*sz);
#endif
}

void* mt_calloc(const size_t n, const size_t sz)
{
#ifdef MEMTEST
  void* p = calloc(n, sz*2); // use calloc, as we want all zeroes
  if (p)
  {
    Reserved* r = (Reserved*)malloc(sizeof(Reserved));
    assert(r);
    r->base = p;
    r->data = ((intptr_t)(n*sz) >> 1) + p;
    r->dend = r->data + r->size * r->num;
    r->end = p + n*sz*2;
    r->num = n;
    r->size = sz;
    r->next = NULL;

    if (root)
      last()->next = r;
    else
      root = r;

    if (!registeredExit)
      registeredExit = !atexit(mt_check);

    return r->data;
  }
  return NULL;
#else
  return calloc(n, sz);
#endif
}

void underwrite(const Reserved* const node)
{
  size_t badBytes = 0;
  for (void* i = node->base; i < node->data; ++i)
  {
    if (*((char*)i) != PADDING)
      ++badBytes;
  }
  if (!badBytes)
    return;
  fprintf(stderr, "Underwrite detected from %p. Base: %p, size: %zu, num: %zu\n",
          node->data, node->base, node->size, node->num);
  for (void* i = node->base; i < node->data; ++i)
  {
    if (*((char*)i) != PADDING)
    {
      fprintf(stderr, "\tByte %zu has value %x\n",
              (size_t)(i - node->base), *((char*)i));
    }
  }
}

void overwrite(const Reserved* const node)
{
  size_t badBytes = 0;
  for (void* i = node->dend; i < node->end; ++i)
  {
    if (*((char*)i) != PADDING)
      ++badBytes;
  }
  if (!badBytes)
    return;
  fprintf(stderr, "Overwrite detected from %p. Base: %p, size: %zu, num: %zu\n",
          node->data, node->base, node->size, node->num);
  for (void* i = node->dend; i < node->end; ++i)
  {
    if (*((char*)i) != PADDING)
    {
      fprintf(stderr, "\tByte %zu has value %x\n",
              (size_t)(i - node->base), *((char*)i));
    }
  }
}

void mt_free(void* p)
{
#ifdef MEMTEST
  if (!p)
    return;

  if (!root)
  {
    fprintf(stderr, "Called mt_free() but root node not reserved. Exiting\n");
    abort();
  }


  Reserved* prev;
  Reserved* node = root;
  if (root->data == p)
  {
    prev = NULL;
  }
  else
  {
    while (node && node->data != p)
    {
      prev = node;
      node = node->next;
    }
  }

  if (!node)
  {
    fprintf(stderr, "Called mt_free() on %p, but it wasn't reserved. Exiting\n", p);
    abort();
  }

  // check for any under or overwrites
  underwrite(node);
  overwrite(node);

  // free our base, we're done with the data
  free(node->base);
  if (prev)
    prev->next = node->next; // relink our linked list
  else
    root = node->next;
  free(node); // cull the node
#else
  free(p);
#endif
}

void mt_check(void)
{
#ifndef MEMTEST
  return;
#endif

  size_t leaks = 0;
  size_t bytes = 0;
  while (root)
  {
    size_t l = root->num * root->size;
    bytes += l;
    ++leaks;
    fprintf(stderr, "Leaked block of %zu bytes of memory at %p (%p)\n", l, root->base, root->data);
    mt_free(root->data);
  }
  printf("Found a total of %zu leaks, leaking %zu bytes\n", leaks, bytes);
}
