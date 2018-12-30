#ifndef _IMG_H_
#define _IMG_H_

#include <stdint.h>
#include "bswap.h"

void ci8_to_rgba32(uint32_t *out, uint8_t *ciData, uint16_t *palette, int numPixels);

#endif // _IMG_H_