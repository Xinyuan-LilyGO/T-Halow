#ifndef _LINUX_UNALIGNED_BYTESHIFT_H
#define _LINUX_UNALIGNED_BYTESHIFT_H

static inline uint16 __get_unaligned_le16(const uint8 *p)
{
    return p[0] | p[1] << 8;
}

static inline uint32 __get_unaligned_le32(const uint8 *p)
{
    return p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
}

static inline uint64 __get_unaligned_le64(const uint8 *p)
{
    return (uint64)__get_unaligned_le32(p + 4) << 32 |
           __get_unaligned_le32(p);
}

static inline void __put_unaligned_le16(uint16 val, uint8 *p)
{
    *p++ = val;
    *p++ = val >> 8;
}

static inline void __put_unaligned_le32(uint32 val, uint8 *p)
{
    __put_unaligned_le16(val >> 16, p + 2);
    __put_unaligned_le16(val, p);
}

static inline void __put_unaligned_le64(uint64 val, uint8 *p)
{
    __put_unaligned_le32(val >> 32, p + 4);
    __put_unaligned_le32(val, p);
}

static inline uint16 get_unaligned_le16(const void *p)
{
    return __get_unaligned_le16((const uint8 *)p);
}

static inline uint32 get_unaligned_le32(const void *p)
{
    return __get_unaligned_le32((const uint8 *)p);
}

static inline uint64 get_unaligned_le64(const void *p)
{
    return __get_unaligned_le64((const uint8 *)p);
}

static inline void put_unaligned_le16(uint16 val, void *p)
{
    __put_unaligned_le16(val, (uint8 *)p);
}

static inline void put_unaligned_le32(uint32 val, void *p)
{
    __put_unaligned_le32(val, (uint8 *)p);
}

static inline void put_unaligned_le64(uint64 val, void *p)
{
    __put_unaligned_le64(val, (uint8 *)p);
}

static inline uint16 __get_unaligned_be16(const uint8 *p)
{
    return p[0] << 8 | p[1];
}

static inline uint32 __get_unaligned_be32(const uint8 *p)
{
    return p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
}

static inline uint64 __get_unaligned_be64(const uint8 *p)
{
    return (uint64)__get_unaligned_be32(p) << 32 |
           __get_unaligned_be32(p + 4);
}

static inline void __put_unaligned_be16(uint16 val, uint8 *p)
{
    *p++ = val >> 8;
    *p++ = val;
}

static inline void __put_unaligned_be32(uint32 val, uint8 *p)
{
    __put_unaligned_be16(val >> 16, p);
    __put_unaligned_be16(val, p + 2);
}

static inline void __put_unaligned_be64(uint64 val, uint8 *p)
{
    __put_unaligned_be32(val >> 32, p);
    __put_unaligned_be32(val, p + 4);
}

static inline uint16 get_unaligned_be16(const void *p)
{
    return __get_unaligned_be16((const uint8 *)p);
}

static inline uint32 get_unaligned_be32(const void *p)
{
    return __get_unaligned_be32((const uint8 *)p);
}

static inline uint64 get_unaligned_be64(const void *p)
{
    return __get_unaligned_be64((const uint8 *)p);
}

static inline void put_unaligned_be16(uint16 val, void *p)
{
    __put_unaligned_be16(val, (uint8 *)p);
}

static inline void put_unaligned_be32(uint32 val, void *p)
{
    __put_unaligned_be32(val, (uint8 *)p);
}

static inline void put_unaligned_be64(uint64 val, void *p)
{
    __put_unaligned_be64(val, (uint8 *)p);
}

#endif /* _LINUX_UNALIGNED_LE_BYTESHIFT_H */
