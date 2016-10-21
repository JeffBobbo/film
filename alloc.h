#ifndef ALLOC_H_INCLUDE
#define ALLOC_H_INCLUDE

#include <stdlib.h> // size_t

/**
 * memory test malloc
 * when MEMTEST is defined, mt_malloc performs an allocation with padding,
 * the allocation is stored internally and a pointer that can be used nas
 * normal is returned.
 * If MEMTEST isn't defined, just does malloc from stdlib.h
 * @param n  how many elements to allocate for
 * @param sz how big each element is
 */
void* mt_malloc(const size_t n, const size_t sz);

/**
 * memory test calloc
 * when MEMTEST is defined, mt_calloc performs an allocation with padding,
 * the allocation is stored internally and a pointer that can be used nas
 * normal is returned.
 * If MEMTEST isn't defined, just does calloc from stdlib.h
 * The allocated memory has it's value set to 0, just like calloc
 * @param n  how many elements to allocate for
 * @param sz how big each element is
 */
void* mt_calloc(const size_t n, const size_t sz);

/**
 * memory test free
 * works just like free(). When MEMTEST is defined it should only be used on
 * pointers allocated with the memory test functions, calling on memory that
 * wasn't allocated by a memory test function will cause an abort.
 * This function will print any under or overwrites to stderr.
 * @param p pointer to free
 */
void mt_free(void* p);

/**
 * An internal function to check details and clean up of any leaked memory.
 * It is called automatically on exit via atexit()
 * When MEMTEST isn't defined, has no effect
 */
void mt_check();

#endif
