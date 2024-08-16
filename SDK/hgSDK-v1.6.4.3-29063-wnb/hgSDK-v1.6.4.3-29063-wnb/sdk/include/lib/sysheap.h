
#ifndef _SYS_HEAP_H_
#define _SYS_HEAP_H_

int sysheap_init(void *heap_start, unsigned int heap_size);
void *sysheap_alloc(int size, const char *func, int line);
int sysheap_free(void *ptr);
void sysheap_collect_init(void);
#ifdef MPOOL_ALLOC
void sysheap_status(void);
#else
#define sysheap_status()
#endif
#endif

