#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "crc.h"

void sendingoutframe(int *seq,FILE *fp);

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