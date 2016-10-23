#include "llist.h"
#include "alloc.h"

#include <stdlib.h> // size_t
#include <assert.h> // assert

typedef struct linkednode_t
{
  struct linkednode_t* prev;
  struct linkednode_t* next;
  void* data;
} LinkedNode;

typedef struct linkedlist_t
{
  size_t size;
  LinkedNode* head;
  LinkedNode* tail;
} LinkedList;

LinkedList* ll_new()
{
  LinkedList* list = (LinkedList*)mt_malloc(sizeof(LinkedList));
  if (list)
  {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
  }
  return list;
}

size_t ll_size(const LinkedList* const ll)
{
  assert(ll);
  return ll->size;
}

bool ll_empty(const LinkedList* const ll)
{
  assert(ll);
  return ll->size ? true : false;
}

LinkedNode* ll_node_new()
{
  LinkedNode* node = (LinkedNode*)mt_malloc(sizeof(LinkedNode));
  if (!node)
    abort();
  node->prev = node->next = NULL;
  node->data = NULL;
  return node;
}
void ll_node_delete(LinkedNode* node)
{
  mt_free(node->data);
  mt_free(node);
}

LinkedNode* ll_front_node(const LinkedList* const ll)
{
  assert(ll);
  return ll->head;
}
LinkedNode* ll_back_node(const LinkedList* const ll)
{
  assert(ll);
  return ll->tail;
}

void* ll_front(const LinkedList* const ll)
{
  LinkedNode* head = ll_front_node(ll);
  return head ? head->data : NULL;
}
void* ll_back(const LinkedList* const ll)
{
  LinkedNode* tail = ll_back_node(ll);
  return tail ? tail->data : NULL;
}

void ll_push_front(LinkedList* const ll, void* p)
{
  assert(ll);
  assert(p);

  LinkedNode* n = ll_node_new();
  n->data = p;

  if (ll->head)
  {
    ll->head->prev = n;
    n->next = ll->head;

    ll->head = n;
  }
  else
  {
    ll->head = n;
    ll->tail = n;
  }
  ++(ll->size);
}

void ll_push_back(LinkedList* const ll, void* p)
{
  assert(ll);
  assert(p);

  LinkedNode* n = ll_node_new();
  n->data = p;

  if (ll->tail)
  {
    ll->tail->next = n;
    n->prev = ll->tail;

    ll->tail = n;
  }
  else
  {
    ll->tail = n;
    ll->head = n;
  }
  ++(ll->size);
}

void ll_pop_front(LinkedList* const ll)
{
  assert(ll);

  LinkedNode* front = ll_front_node(ll);
  if (!front)
    return;

  ll->head = front->next;
  if (ll->head)
    ll->head->prev = NULL;
  ll_node_delete(front);
  --(ll->size);
}

void ll_pop_back(LinkedList* const ll)
{
  assert(ll);

  LinkedNode* back = ll_back_node(ll);
  if (!back)

  back->prev->next = NULL;
  ll_node_delete(back);
  --(ll->size);
}

LinkedNode* ll_at_node(const LinkedList* const ll, const size_t n)
{
  assert(ll);
  LinkedNode* node = ll->head;

  if (n >= ll->size)
    return NULL;

  for (size_t i = 0; i < n; ++i)
    node = node->next;
  return node;
}


void* ll_at(const LinkedList* const ll, const size_t n)
{
  LinkedNode* at = ll_at_node(ll, n);
  return at ? at->data : NULL;
}

#ifdef LL_CONSOLIDATE
void** ll_consolidate(const LinkedList* const ll, size_t* const length)
{
  assert(ll);

  void** ret = (void**)mt_calloc(ll->size, sizeof(void*));

  size_t inserted = 0;
  for (LinkedNode* node = ll_front_node(ll); node; node = node->next)
    ret[inserted++] = node->data;

  *length = ll->size;
  return ret;
}
#endif

void swap(void** a, void** b)
{
  void* p = *a;
  *a = *b;
  *b = p;
}
void ll_bsort(LinkedList* const ll,
             bool (*comparison)(const void* const a, const void* const b))
{
  assert(ll);
  if (ll->size <= 1) // nothing to do
    return;

  bool swapped;
  do
  {
    swapped = false;
    LinkedNode* node = ll_front_node(ll);
    while (node && node->next)
    {
      if ((*comparison)(node->data, node->next->data))
      {
        swap(&node->data, &node->next->data);
        swapped = true;
      }
      node = node->next;
    }
  }
  while (swapped);
}

void ll_clear(LinkedList* ll)
{
  while (ll->head)
  {
    LinkedNode* n = ll->head->next;
    mt_free(ll->head->data);
    mt_free(ll->head);
    ll->head = n;
  }
  ll->tail = NULL;
  ll->size = 0;
}
void ll_delete(LinkedList* ll)
{
  while (ll->head)
  {
    LinkedNode* n = ll->head->next;
    mt_free(ll->head);
    ll->head = n;
  }
  ll->tail = NULL;
  ll->size = 0;
}
void ll_purge(LinkedList* ll)
{
  while (ll_front_node(ll))
    ll_pop_front(ll);
  mt_free(ll);
}

typedef struct linkediterator_t
{
  LinkedList* list;
  LinkedNode* current;
} LinkedIterator;

void* ll_it_begin(LinkedIterator* const it, LinkedList* ll)
{
  it->list = ll;
  it->current = ll_front_node(ll);
  return it->current ? it->current->data : NULL;
}
void* ll_it_rbegin(LinkedIterator* const it, LinkedList* ll)
{
  it->list = ll;
  it->current = ll_back_node(ll);
  return it->current ? it->current->data : NULL;
}

void* ll_it_next(LinkedIterator* const it)
{
  if (it->current->next)
  {
    it->current = it->current->next;
    return it->current->data;
  }
  return NULL;
}
void* ll_it_rnext(LinkedIterator* const it)
{
  if (it->current->prev)
  {
    it->current = it->current->prev;
    return it->current->data;
  }
  return NULL;
}
