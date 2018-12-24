#ifndef _BSWAP_H_
#define _BSWAP_H_

#include <stdint.h>

#define BSWAP32(v) ((((v) & 0x000000FF) << 24) | \
                    (((v) & 0x0000FF00) <<  8) | \
                    (((v) & 0x00FF0000) >>  8) | \
                    (((v) & 0xFF000000) >> 24))

#define BSWAP16(v) ((((v) & 0x00FF) << 8) | \
                    (((v) & 0xFF00) >> 8))

#define BSWAP32_F(v) \
{\
    float _v = (v); \
    uint32_t bits = BSWAP32(*(uint32_t*)&_v);\
    *(float*)bits; \
}

#define U32_BE(ptr, offs) BSWAP32(*(uint32_t*)(((char*)ptr)+offs))
#define U16_BE(ptr, offs) BSWAP16(*(uint16_t*)(((char*)ptr)+offs))
    

#endif // _BSWAP_H_