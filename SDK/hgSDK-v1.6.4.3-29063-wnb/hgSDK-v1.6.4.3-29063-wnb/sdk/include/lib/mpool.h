#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_MAX (12)
#define BLOCK_ID(p, addr)     (((unsigned int) (addr) - (p)->heap_start) / (p)->block_size)
#define BLOCK_ADDR(p, block)  ((void *) ((block) * (p)->block_size + (p)->heap_start))
#define BLOCK_COUNT(p, size)  (((size) + (p)->block_size - 1) / (p)->block_size)

/*free frag list*/
struct frag_list {
    struct frag_list *next;
    struct frag_list *prev;
};

struct block_info {
    union {
        struct {
            int log;
            union {
                struct {
                    unsigned int nfree; //free frag count in the block
                } frag;
                int size; //block count in the block_info
            } info;
        } busy;
        struct {
            unsigned int size; //free block count in current block_info
            unsigned int next; /*next free block id*/
            unsigned int prev; /*prev free block id*/
        } free;
    };
};

struct mem_pool {
    unsigned int block_size;
    unsigned int block_count;
    unsigned int heap_start;
    unsigned int heap_end;
    unsigned int heap_ptr;
    unsigned int heap_base;
    struct frag_list  frags[LOG_MAX];
    struct block_info *blocks;
};

#define mpool_free_size(pool) ((pool)->heap_end-(pool)->heap_ptr)
int mpool_init(struct mem_pool *pool, unsigned int block_size, unsigned int mem_addr, unsigned int mem_size);
void mpool_free(struct mem_pool *pool, void *ptr);
void *mpool_alloc(struct mem_pool *pool, unsigned int size);
void mpool_state(struct mem_pool *pool, char *state_buf, int32 buf_size);

#ifdef __cplusplus
}
#endif
#endif
