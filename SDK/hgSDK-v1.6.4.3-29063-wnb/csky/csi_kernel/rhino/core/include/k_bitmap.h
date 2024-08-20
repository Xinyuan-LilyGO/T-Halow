/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef K_BITMAP_H
#define K_BITMAP_H

#define BITMAP_UNIT_SIZE 32U
#define BITMAP_UNIT_MASK 0X0000001F
#define BITMAP_UNIT_BITS 5U

#define BITMAP_MASK(nr) (1UL << (BITMAP_UNIT_SIZE - 1U - ((nr) & BITMAP_UNIT_MASK)))
#define BITMAP_WORD(nr) ((nr) >> BITMAP_UNIT_BITS)


#define LITTLE_TO_BIG_ENDIAN(x) ((uint32_t)(((x) & 0x000000ffUL) << 24u) | \
                                (((x) & 0x0000ff00UL) << 8u) | \
                                (((x) & 0x00ff0000UL) >> 8u) | \
                                (((x) & 0xff000000UL) >> 24u))

/**
 ** This MACRO will declare a bitmap
 ** @param[in]  name  the name of the bitmap to declare
 ** @param[in]  bits  the bits of the bitmap
 ** @return  no return
 **/
#define BITMAP_DECLARE(name, bits) uint32_t name[((bits) + (BITMAP_UNIT_SIZE - 1U)) >> BITMAP_UNIT_BITS]

#if (RHINO_CONFIG_BITMAP_HW != 0)
extern int32_t cpu_bitmap_clz(uint32_t val);
#endif

/**
 ** This function will set a bit of the bitmap
 ** @param[in]  bitmap  pointer to the bitmap
 ** @param[in]  nr      position of the bitmap to set
 ** @return  no return
 **/
RHINO_INLINE void krhino_bitmap_set(uint32_t *bitmap, int32_t nr)
{
    bitmap[BITMAP_WORD(nr)] |= BITMAP_MASK(nr);
}

/**
 ** This function will clear a bit of the bitmap
 ** @param[in]  bitmap  pointer to the bitmap
 ** @param[in]  nr      position of the bitmap to clear
 ** @return  no return
 **/
RHINO_INLINE void krhino_bitmap_clear(uint32_t *bitmap, int32_t nr)
{
    bitmap[BITMAP_WORD(nr)] &= ~BITMAP_MASK(nr);
}

/**
 ** This function will find the first bit(1) of the bitmap
 ** @param[in]  bitmap  pointer to the bitmap
 ** @return  the first bit position
 **/
RHINO_INLINE int krhino_find_first_bit(uint32_t *bitmap)
{
    int32_t  nr  = 0;
    uint32_t tmp = 0;

    while (*bitmap == 0UL) {
        nr += BITMAP_UNIT_SIZE;
        bitmap++;
    }

    tmp = *bitmap;

#if (RHINO_CONFIG_LITTLE_ENDIAN == 0)
    tmp = LITTLE_TO_BIG_ENDIAN(tmp);
#endif

#if (RHINO_CONFIG_BITMAP_HW == 0)
    if (!(tmp & 0XFFFF0000)) {
        tmp <<= 16;
        nr   += 16;
    }

    if (!(tmp & 0XFF000000)) {
        tmp <<= 8;
        nr   += 8;
    }

    if (!(tmp & 0XF0000000)) {
        tmp <<= 4;
        nr   += 4;
    }

    if (!(tmp & 0XC0000000)) {
        tmp <<= 2;
        nr   += 2;
    }

    if (!(tmp & 0X80000000)) {
        nr   += 1;
    }
#else
    nr += cpu_bitmap_clz(tmp);
#endif

    return nr;
}

#endif /* K_BITMAP_H */

