#ifndef LLIST_H_INCLUDE
#define LLIST_H_INCLUDE

#include <stdlib.h> // size_t
#include <stdbool.h>

typedef struct linkedlist_t LinkedList;
typedef struct linkednode_t LinkedNode;

LinkedList* ll_new();

size_t ll_size(const LinkedList* const ll);
bool ll_empty(const LinkedList* const ll);

void* ll_front(const LinkedList* const ll);
void* ll_back(const LinkedList* const ll);

void ll_push_front(LinkedList* const ll, void* p);
void ll_push_back(LinkedList* const ll, void* p);

void ll_pop_front(LinkedList* const ll);
void ll_pop_back(LinkedList* const ll);

void* ll_at(const LinkedList* const ll, const size_t n);

#ifdef LL_CONSOLIDATE
void** ll_consolidate(const LinkedList* const ll, size_t* const length);
#endif

void ll_delete(LinkedList* ll);

#endif
