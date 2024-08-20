/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_LWIPOPTS_H
#define LWIP_HDR_LWIPOPTS_H

//#define LWIP_PORTING_PRINTF
#ifdef LWIP_PORTING_PRINTF
#define lwip_printf(fmt, ...) printf("%s:%d::"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define lwip_printf(fmt, ...) do{}while(0)
#endif

#define MEM_LIBC_MALLOC 1

#define LWIP_TRANSPORT_ETHERNET       1

#define MEM_SIZE                      (64*1024)//(8*1024)//(16*1024)

/* We link to special sys_arch.c (for basic non-waiting API layers unit tests) */
#define NO_SYS                          0
#define LWIP_IPV4                   1

#define LWIP_IPV6                   0

#if !LWIP_IPV4 && !LWIP_IPV4
#error "Either IPv4 or IPv6 must be enabled."
#endif
#define SYS_LIGHTWEIGHT_PROT            1
#define LWIP_NETCONN                    !NO_SYS

#define LWIP_RAW                    1

#define TCPIP_MBOX_SIZE             256
#define DEFAULT_TCP_RECVMBOX_SIZE   64
#define DEFAULT_UDP_RECVMBOX_SIZE   64
#define DEFAULT_RAW_RECVMBOX_SIZE   64
#define DEFAULT_ACCEPTMBOX_SIZE     64

#ifdef LWIP_DEBUG
#define TCPIP_THREAD_STACKSIZE      4096
#else
#define TCPIP_THREAD_STACKSIZE      2048
#endif

#define TCPIP_THREAD_PRIO           OS_TASK_PRIORITY_NORMAL//OS_TASK_PRIORITY_ABOVE_NORMAL

#ifdef LWIP_DEBUG
#define DEFAULT_THREAD_STACKSIZE    512*2
#else
#define DEFAULT_THREAD_STACKSIZE    512
#endif

#define MEMP_NUM_SYS_TIMEOUT        16

// 32-bit alignment
#define MEM_ALIGNMENT               4

//#define LWIP_RAM_HEAP_POINTER       lwip_ram_heap

// Number of pool pbufs.
// Each requires 684 bytes of RAM.
#define PBUF_POOL_SIZE              32

// One tcp_pcb_listen is needed for each TCPServer.
// Each requires 72 bytes of RAM.
#define MEMP_NUM_TCP_PCB_LISTEN     4


// One is tcp_pcb needed for each TCPSocket.
// Each requires 196 bytes of RAM.
#define MEMP_NUM_TCP_PCB            4

// One udp_pcb is needed for each UDPSocket.
// Each requires 84 bytes of RAM (total rounded to multiple of 512).

#define MEMP_NUM_UDP_PCB            4

// Number of non-pool pbufs.
// Each requires 92 bytes of RAM.
#define MEMP_NUM_PBUF               128

// Each netbuf requires 64 bytes of RAM.
#define MEMP_NUM_NETBUF             4

#define MEMP_NUM_TCP_SEG            256

#define TCP_MSS                     1460

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF                 64*TCP_MSS

#define TCP_SND_QUEUELEN            (4 * TCP_SND_BUF/TCP_MSS)

#define TCP_SNDLOWAT                (TCP_SND_BUF/2)
#define TCP_SNDQUEUELOWAT           LWIP_MAX(((TCP_SND_QUEUELEN)/2), 5)

#define LWIP_WND_SCALE                  1

#define TCP_RCV_SCALE                   2

#define TCP_WND                         16384

#define LWIP_TCP_TIMESTAMPS             0

#define LWIP_TCPIP_CORE_LOCKING         0

//#define MEM_USE_POOLS_TRY_BIGGER_POOL   1


/**
 * LWIP_SO_SNDTIMEO==1: Enable send timeout for sockets/netconns and
 * SO_SNDTIMEO processing.
 */
#define LWIP_SO_SNDTIMEO                1

/**
 * LWIP_SO_RCVTIMEO==1: Enable receive timeout for sockets/netconns and
 * SO_RCVTIMEO processing.
 */
#define LWIP_SO_RCVTIMEO                1

#define LWIP_SO_SNDRCVTIMEO_NONSTANDARD 1

/**
 * MEMP_NUM_TCPIP_MSG_API: the number of struct tcpip_msg, which are used
 * for callback/timeout API communication.
 * (only needed if you use tcpip.c)
 */
#define MEMP_NUM_TCPIP_MSG_API          32

/**
 * MEMP_NUM_TCPIP_MSG_INPKT: the number of struct tcpip_msg, which are used
 * for incoming packets.
 * (only needed if you use tcpip.c)
 */
#define MEMP_NUM_TCPIP_MSG_INPKT        64

#ifndef MEMCPY
extern void hw_memcpy(void *dest, const void *src, unsigned int size);
#define MEMCPY(dst,src,len)             hw_memcpy(dst,src,len)
#endif

/**
 * SMEMCPY: override this with care! Some compilers (e.g. gcc) can inline a
 * call to memcpy() if the length is known at compile time and is small.
 */
#ifndef SMEMCPY
extern void hw_memcpy(void *dest, const void *src, unsigned int size);
#define SMEMCPY(dst,src,len)            hw_memcpy(dst,src,len)
#endif


#define MEMP_NUM_REASSDATA              10

// One netconn is needed for each UDPSocket, TCPSocket or TCPServer.
// Each requires 236 bytes of RAM (total rounded to multiple of 512).
#define MEMP_NUM_NETCONN            4

/**
 * LWIP_SO_RCVBUF==1: Enable SO_RCVBUF processing.
 */

#define TCP_QUEUE_OOSEQ             1

#define LWIP_DHCP                   LWIP_IPV4
#define LWIP_DNS                    1
#define LWIP_SOCKET                 1

#define SO_REUSE                    1

// Support Multicast
#include "stdlib.h"
#define LWIP_IGMP                   0 //LWIP_IPV4
#define LWIP_RAND()                 rand()

#define LWIP_COMPAT_SOCKETS         1
#define LWIP_POSIX_SOCKETS_IO_NAMES 0
#define LWIP_SO_RCVTIMEO            1
#define LWIP_TCP_KEEPALIVE          1

// Fragmentation on, as per IPv4 default
#define LWIP_IPV6_FRAG              LWIP_IPV6

// Queuing "disabled", as per IPv4 default (so actually queues 1)
#define LWIP_ND6_QUEUEING           0

// Debug Options
#define NETIF_DEBUG                 LWIP_DBG_OFF
#define PBUF_DEBUG                  LWIP_DBG_OFF
#define API_LIB_DEBUG               LWIP_DBG_OFF
#define API_MSG_DEBUG               LWIP_DBG_OFF
#define SOCKETS_DEBUG               LWIP_DBG_OFF
#define ICMP_DEBUG                  LWIP_DBG_OFF
#define IGMP_DEBUG                  LWIP_DBG_OFF
#define INET_DEBUG                  LWIP_DBG_OFF
#define IP_DEBUG                    LWIP_DBG_OFF
#define IP_REASS_DEBUG              LWIP_DBG_OFF
#define RAW_DEBUG                   LWIP_DBG_OFF
#define MEM_DEBUG                   LWIP_DBG_OFF
#define MEMP_DEBUG                  LWIP_DBG_OFF
#define SYS_DEBUG                   LWIP_DBG_OFF
#define TIMERS_DEBUG                LWIP_DBG_OFF
#define TCP_DEBUG                   LWIP_DBG_OFF
#define TCP_INPUT_DEBUG             LWIP_DBG_OFF
#define TCP_FR_DEBUG                LWIP_DBG_OFF
#define TCP_RTO_DEBUG               LWIP_DBG_OFF
#define TCP_CWND_DEBUG              LWIP_DBG_OFF
#define TCP_WND_DEBUG               LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG            LWIP_DBG_OFF
#define TCP_RST_DEBUG               LWIP_DBG_OFF
#define TCP_QLEN_DEBUG              LWIP_DBG_OFF
#define UDP_DEBUG                   LWIP_DBG_OFF
#define TCPIP_DEBUG                 LWIP_DBG_OFF
#define SLIP_DEBUG                  LWIP_DBG_OFF
#define DHCP_DEBUG                  LWIP_DBG_OFF
#define AUTOIP_DEBUG                LWIP_DBG_OFF
#define DNS_DEBUG                   LWIP_DBG_OFF
#define IP6_DEBUG                   LWIP_DBG_OFF

#define PPP_DEBUG                   LWIP_DBG_OFF
#define ETHARP_DEBUG                LWIP_DBG_OFF
#define UDP_LPC_EMAC                LWIP_DBG_OFF

#ifdef LWIP_DEBUG
#define MEMP_OVERFLOW_CHECK         1
#define MEMP_SANITY_CHECK           1
#else
#define LWIP_NOASSERT               1
#define LWIP_STATS                  0
#endif

#define LWIP_DBG_TYPES_ON           LWIP_DBG_ON
#define LWIP_DBG_MIN_LEVEL          LWIP_DBG_LEVEL_ALL

#define LWIP_PLATFORM_BYTESWAP      1

#define LWIP_RANDOMIZE_INITIAL_LOCAL_PORTS 1

#ifndef MAC2STR
#define MAC2STR(a) (a)[0]&0xff, (a)[1]&0xff, (a)[2]&0xff, (a)[3]&0xff, (a)[4]&0xff, (a)[5]&0xff
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif
    
#ifndef STR2MAC
#define STR2MAC(s, a) str2mac((const uint8 *)(s), (uint8 *)(a))
#endif


#if LWIP_TRANSPORT_ETHERNET

// Broadcast
#define IP_SOF_BROADCAST            0
#define IP_SOF_BROADCAST_RECV       0

#define LWIP_BROADCAST_PING         1

#define LWIP_CHECKSUM_ON_COPY       0

#define LWIP_NETIF_HOSTNAME         1
#define LWIP_NETIF_STATUS_CALLBACK  1
#define LWIP_NETIF_LINK_CALLBACK    1

#elif LWIP_TRANSPORT_PPP

#define TCP_SND_BUF                     (3 * 536)
#define TCP_WND                         (2 * 536)

#define LWIP_ARP 0

#define PPP_SUPPORT 0
#define CHAP_SUPPORT                    1
#define PAP_SUPPORT                     1
#define PPP_THREAD_STACKSIZE            4*192
#define PPP_THREAD_PRIO 0

#define MAXNAMELEN                      64     /* max length of hostname or name for auth */
#define MAXSECRETLEN                    64

#define MEM_OVERFLOW_CHECK              0

#else
#error A transport mechanism (Ethernet or PPP) must be defined
#endif

#endif /* LWIPOPTS_H_ */
