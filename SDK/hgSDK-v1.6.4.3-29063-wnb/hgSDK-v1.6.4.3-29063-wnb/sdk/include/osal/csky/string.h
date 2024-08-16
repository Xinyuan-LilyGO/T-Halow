
#ifndef _OS_CSKY_STDLIB_H_
#define _OS_CSKY_STDLIB_H_
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "osal/sleep.h"

#ifdef __cplusplus
extern "C" {
#endif

#define os_abs             abs
#define os_atoi(c)         atoi((const char *)c)
#define os_strcpy(d,s)     strcpy((char *)(d), (const char *)(s))
#define os_strncpy(d,s,n)  strncpy((char *)(d), (const char *)(s), n)
#define os_strcmp(s1,s2)   strcmp((const char *)(s1), (const char *)(s2))
#define os_strstr(s1,s2)   strstr((const char *)(s1), (const char *)(s2))
#define os_strchr(s,c)     strchr((const char *)(s), c)
#define os_strlen(s)       strlen((const char *)(s))
#define os_memset(s,c,n)   memset((void *)(s), c, n)
#define os_memcpy(d,s,n)   memcpy((void *)(d), (const void *)(s), n)
#define os_memcmp(s1,s2,n) memcmp((const void *)(s1), (const void *)(s2), n)
#define os_memmove(d,s,n)  memmove((void *)(d), (const void *)(s), n)
#define os_sprintf(s, ...) sprintf((char *)(s), __VA_ARGS__)
#define os_vsnprintf       vsnprintf
#define os_strncmp(s1,s2,n) strncmp((const char *)s1, (const char *)s2, n)
#define os_snprintf        snprintf
#define os_strdup          strdup
#define os_strrchr(s,c)    strrchr((const char *)(s), c)
#define os_strncasecmp(s1,s2,n)  strncasecmp((const char *)(s1), (const char *)(s2), n)
#define os_strcasecmp(s1,s2)     strcasecmp((const char *)(s1), (const char *)(s2))
#define os_srand(v)        srand(v)
//#define os_rand()          rand()
#define os_sscanf          sscanf
#define os_htons(x) ((((x) & 0x00ffUL) << 8) | (((x) & 0xff00UL) >> 8))
#define os_ntohs(x) os_htons(x)
#define os_htonl(x) ((((x) & 0x000000ffUL) << 24) | \
                      (((x) & 0x0000ff00UL) <<  8) | \
                       (((x) & 0x00ff0000UL) >>  8) | \
                        (((x) & 0xff000000UL) >> 24))
#define os_ntohl(x) os_htonl(x)

#if 0
#define os_printf(fmt, ...) ({\
        print_lock();\
        printf("[%d]"fmt, os_jiffies(), ##__VA_ARGS__);\
        print_unlock();\
    })
#else
#define os_printf(fmt, ...)  hgprintf("[%u]"fmt, os_jiffies(), ##__VA_ARGS__)
#define _os_printf(fmt, ...) hgprintf(fmt, ##__VA_ARGS__)
#endif

void print_lock(void);
void print_unlock(void);
int strncasecmp(const char *s1, const char *s2, int n);
int strcasecmp(const char *s1, const char *s2);
uint32 os_atoh(char *str);

#ifdef __cplusplus
}
#endif

#endif


