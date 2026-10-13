#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

uint16_t crc16(const char *text)
{
    uint16_t crc = 0xFFFF;
    for(int i = 0 ; i < strlen(text) ; i++)
    {
        crc = crc ^ (text[i] << 8 );
        // printf("%c = %d  crc = %d\n", text[i], text[i], crc);
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
    // printf("%d\n",crc);
    return crc;
}

void sendingoutframe(int *seq,FILE *fp)
{
    float temp = 25.6;
    float hum = 60.5;
    char frame[80];
    char body[64];
    
    temp = (rand()% 374) - 273 ;
    hum = rand()%101 + 1;
    snprintf(body,sizeof(body),"AA55,1,%04d,%.1f,%.1f",*seq,temp,hum);
    printf("%s\n",body);
    uint16_t crc = crc16(body);
    snprintf(frame,sizeof(frame),"%s,%04X",body,crc);
    printf("%s\n",frame);
    fprintf(fp, "%s\n" ,frame);

}

int main()
{
    FILE *fp = fopen("telemetry.txt","w");
    int seq;
    srand(time(NULL));
    for(seq = 1 ; seq <= 10 ; seq++)
    {
        sendingoutframe(&seq,fp);
    }
    fclose(fp);
    return 0;
}