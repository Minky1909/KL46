#ifndef _PARSE_SREC_H_                                          /* Header guard */
#define _PARSE_SREC_H_

#include <stdio.h>
#include <stdint.h>

#define MAX_ARRAY_DATA 16

uint32_t GetAddress(int8_t *buffer);

uint32_t GetData(int8_t *buffer, uint8_t i);


#endif
