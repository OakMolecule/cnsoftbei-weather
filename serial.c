#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringSerial.h>

#include "tts.c"
#include "mqtt.h"
#include "MQTTClient.h"

int initSerial(const char *device, const int baund)
{
    int fd ;

    if ((fd = serialOpen (device, baund)) < 0)
    {
        fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    }
    return fd;
}

void readSerial (int fd)
{

    // Loop, getting and printing characters
    char cmd[10];
    int i;

    i = 0;
    while(serialDataAvail(fd))
    {
        cmd[i] = (char)serialGetchar (fd);
        putchar(cmd[i]);
        if(cmd[i] == '\n')
        {
            break;
            cmd[i] = '\0';
        }
        i++;
    }
    cmd[i] = '\0';
    if (strcmp(cmd, "shoudao"))
    {
        printf("%s", cmd);
        strcpy(cmd, "");
    } else if(strcmp(cmd, "woele"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        pubmsg.payload = "water";
        pubmsg.payloadlen = strlen("water");
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_subcribe(client, TOPIC_TING, &pubmsg, &token);
        system("aplay -c 1 -t raw -r 16000 -f mu_law qushui.wav");
    } else if(strcmp(cmd, "wokele"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        pubmsg.payload = "fruit";
        pubmsg.payloadlen = strlen("fruit");
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_subcribe(client, TOPIC_TING, &pubmsg, &token);
        system("aplay -c 1 -t raw -r 16000 -f mu_law shuiguo.wav");
    } else if(strcmp(cmd, "tianqi"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        playWeather();
    } else if(strcmp(cmd, "guandeng"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
    } else if(strcmp(cmd, "kaideng"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
    }
    fflush (stdout) ;
}

