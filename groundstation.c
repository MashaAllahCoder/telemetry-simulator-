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

int main()
{
    int total_frame = 0 ,correct_frame = 0,incorrect_frame = 0;
    FILE *fp = fopen("telemetry.txt","r");
    char line[100];
    if(fp == NULL)
    {
        printf("cannot open the file");
        return 1;
    }
    while (fgets(line,sizeof(line),fp) != NULL)
    {
        char *lastComma = strrchr(line, ',');
        line[strcspn(line, "\n")] = '\0';   
        *lastComma = '\0';
        printf("[%s]\n",line);
        uint16_t calc_crc = crc16(line);
        long attached = strtol(lastComma+1,NULL, 16 );
        if (calc_crc != attached)
        {
            printf("Error detected : %s\n",line);
            incorrect_frame++;
        }
        else
        {
            printf("No error detected : %s\n",line);
            correct_frame++;
        }
        total_frame++;
    }
    char conclusion[100];
    snprintf(conclusion,sizeof(conclusion),"Total frame = %d\nCorrect frame = %d\nIncorrect frame = %d\n",total_frame,correct_frame,incorrect_frame);
    printf("%s",conclusion);
    fclose(fp);
    return 0;
}