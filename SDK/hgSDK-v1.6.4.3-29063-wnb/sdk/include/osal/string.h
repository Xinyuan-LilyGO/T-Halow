#ifndef __OS_STRING_H__
#define __OS_STRING_H__
#ifdef __MBED__
#include "osal/mbed/string.h"
#endif

#ifdef __CSKY__
#include "osal/csky/string.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void *_os_malloc(int size);
void _os_free(void *ptr);
void *_os_zalloc(int size);
void *_os_realloc(void *ptr, int size);
void *_os_calloc(size_t nmemb, size_t size);

void *_os_malloc_t(int size, const char *func, int line);
void _os_free_t(void *ptr, const char *func, int line);
void *_os_zalloc_t(int size, const char *func, int line);
void *_os_realloc_t(void *ptr, int size, const char *func, int line);
void *_os_calloc_t(size_t nmemb, size_t size, const char *func, int line);

void hw_memcpy(void *dest, const void *src, uint32 size);
void hw_memset(void * dest, uint8 val, uint32 n);

//#define MEM_TRACE

#ifdef MEM_TRACE //mem leak trace
#ifndef os_malloc
#define os_malloc(s) _os_malloc_t(s, __FUNCTION__, __LINE__)
#endif
#ifndef os_free
#define os_free(p)   do{ _os_free_t((void *)p, __FUNCTION__, __LINE__); (p)=NULL;}while(0)
#endif
#ifndef os_zalloc
#define os_zalloc(s) _os_zalloc_t(s, __FUNCTION__, __LINE__)
#endif
#ifndef os_realloc
#define os_realloc(p,s) _os_realloc_t(p, s, __FUNCTION__, __LINE__)
#endif
#ifndef os_calloc
#define os_calloc(p,s) _os_calloc_t(p, s, __FUNCTION__, __LINE__)
#endif
#else
#ifndef os_malloc
#define os_malloc(s) _os_malloc(s)
#endif
#ifndef os_free
#define os_free(p)   do{ _os_free((void *)p); (p)=NULL;}while(0)
#endif
#ifndef os_zalloc
#define os_zalloc(s) _os_zalloc(s)
#endif
#ifndef os_realloc
#define os_realloc(p,s) _os_realloc(p,s)
#endif
#ifndef os_calloc
#define os_calloc(p,s) _os_calloc(p, s)
#endif
#endif

void disable_print(void);
void enable_print(void);

#if ERRLOG_SIZE
void errlog_flush(void);
void errlog_action(uint8 action);
#else
#define errlog_flush()
#define errlog_action(action)
#endif

int32 hex2int(char c);
int32 hex2char(char *hex);
int32 hex2bin(char *hex, uint8 *buf, uint32 len);
void str2mac(char *macstr, uint8 *mac);

#ifndef MAC2STR
#define MAC2STR(a) (a)[0]&0xff, (a)[1]&0xff, (a)[2]&0xff, (a)[3]&0xff, (a)[4]&0xff, (a)[5]&0xff
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif
    
#ifndef STR2MAC
#define STR2MAC(s, a) str2mac((char *)(s), (uint8 *)(a))
#endif

#ifndef IP2STR
#define IP2STR(ip) ((ip)>>24)&0xff,((ip)>>16)&0xff,((ip)>>8)&0xff,(ip&0xff)
#define IPSTR "%d.%d.%d.%d"
#endif

void hgprintf(const char *fmt, ...);
void osprint_redirect(void (*print)(char *msg));
void hgprintf_out(char *str, int32 len);

void dump_hex(char *str, uint8 *data, uint32 len);
void dump_key(uint8 *str, uint8 *key, uint32 len);
uint32 os_rand(void);

#ifdef __cplusplus
}
#endif
#endif
