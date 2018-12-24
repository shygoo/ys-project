#ifndef _SMSR00_H_
#define _SMSR00_H_

#include <stdint.h>

extern const char SMSR00_SIG[6];

void smsr00_decode(uint8_t *src, uint8_t *dst);
size_t smsr00_get_output_size(uint8_t *src);

#endif // _SMSR00_H_
