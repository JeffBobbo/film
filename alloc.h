#include <stdlib.h>

void* mt_malloc(const size_t n, const size_t sz);
void* mt_calloc(const size_t n, const size_t sz);
void mt_free(void* p);
size_t check();
