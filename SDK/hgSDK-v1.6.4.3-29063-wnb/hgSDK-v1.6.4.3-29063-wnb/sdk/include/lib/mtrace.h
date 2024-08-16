#ifndef _HGIC_SDK_MTRACE_H_
#define _HGIC_SDK_MTRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

struct mtrace_entry {
    void *ptr;
    const char *func;
    int  line;
    int  size;
};

struct mtrace {
    int size;
    struct mtrace_entry *entrys;
};

void mtrace_print(struct mtrace *mt);
void mtrace_add(struct mtrace *mt, void *ptr, const char *func, int line, int size);
void mtrace_del(struct mtrace *mt, void *ptr);

#ifdef __cplusplus
}
#endif
#endif

