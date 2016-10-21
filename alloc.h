#ifndef ALLOC_H_INCLUDE
#define ALLOC_H_INCLUDE

void* mt_malloc(const size_t n, const size_t sz);
void* mt_calloc(const size_t n, const size_t sz);
void mt_free(void* p);
void mt_check();

#endif
