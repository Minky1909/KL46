#include "Parse_Srec.h"

uint32_t GetAddress(int8_t *buffer)
{
    /* buffer[1] = '1' -> 2 byte
     * buffer[1] = '2' -> 3 byte
     * buffer[1] = '3' -> 4 byte */
    uint8_t byte = H1(buffer[1]) + 1;
    uint32_t address = 0;
    int8_t hex[2] = {'0', '0'};
    uint8_t index;
    /* 1 byte -> address = buffer[4: 8]
     * 2 byte -> address = buffer[4: 10]
     * 3 byte -> address = buffer[4: 12]
     * -> address = buffer[4: 4 + 2 * byte] */
    for (index = 4; index < 4 + 2 * byte; index++)
    {
        hex[0] = buffer[index];
        hex[1] = buffer[++index];
        address |= CONVERT_HEX_DEC(hex);
        if (index != (2 * byte + 3))
        {
            address = address << 8;
        }
    }
    return address;
}

uint32_t GetData(int8_t *buffer,uint8_t i)
{
    static uint32_t data[MAX_ARRAY_DATA]; /* Array data */
    int8_t hex[2] = {'0', '0'};
    uint8_t index_data;
    uint8_t index_buffer;
    uint8_t length = 0; /* Length of buffer */


    for(index_data = i; index_data < i + 4; index_data++ )
    {
	
        hex[0] = buffer[8+ 2*i];
        hex[1] = buffer[8 + 2*i+1];
        data[index_data] = CONVERT_HEX_DEC(hex);
    }
    return * data;
}
