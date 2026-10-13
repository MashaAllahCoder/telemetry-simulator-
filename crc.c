#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint16_t crc16(const char *text)
{
    uint16_t crc = 0xFFFF;
    for(int i = 0 ; i < strlen(text) ; i++)
    {
        crc = crc ^ (text[i] << 8 );
        printf("%c = %d  crc = %d\n", text[i], text[i], crc);
        for(int bit = 0 ; bit < 8 ; bit++)
        {
            if (crc &  0x8000)
            {
                crc = (crc << 1) ^ 0x1021;
            }
            else 
            {
                crc = crc << 1;
            }
        }
    }
    printf("%d\n",crc);
    return crc;
}

int main()
{
    // uint16_t input = 0xAA55;
    uint16_t result = crc16("0024");
    printf("%04X\n",result);
    return 0;
}