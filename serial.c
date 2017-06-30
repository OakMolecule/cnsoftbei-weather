#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringSerial.h>
#include <wiringPi.h>

#include "serial.h"
#include "tts.h"
#include "mqtt.h"
#include "MQTTClient.h"

#define LED 4

int call = 0;

int initSerial(const char *device, const int baund)
{
    int fd ;

    pinMode(LED, OUTPUT);
    if ((fd = serialOpen (device, baund)) < 0)
    {
        fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    }
    return fd;
}

void readSerial (int fd)
{

    // Loop, getting and printing characters
    char cmd[10] = "";
    int i;

    i = 0;
    while(serialDataAvail(fd))
    {
        cmd[i] = (char)serialGetchar (fd);
        putchar(cmd[i]);
        if(cmd[i] == '\n' || i == 10)
        {
            break;
            cmd[i] = '\0';
        }
        i++;
    }
    cmd[i] = '\0';
    if (!strcmp(cmd, "shoudao"))
    {
        printf("%s", cmd);
        strcpy(cmd, "");
        system("aplay -c 1 -t raw -r 16000 -f mu_law shoudao.wav");
    } else if(!strcmp(cmd, "woele"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        pubmsg.payload = "fruit";
        pubmsg.payloadlen = strlen("fruit");
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC_TING, &pubmsg, &token);
        system("aplay -c 1 -t raw -r 16000 -f mu_law shuiguo.wav");
    } else if(!strcmp(cmd, "wokele"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        pubmsg.payload = "water";
        pubmsg.payloadlen = strlen("water");
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC_TING, &pubmsg, &token);
        system("aplay -c 1 -t raw -r 16000 -f mu_law qushui.wav");
    } else if(!strcmp(cmd, "tianqi"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        playWeather();
    } else if(strcmp(cmd, "guandeng") == 0)
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        digitalWrite(LED, HIGH);
    } else if(!strcmp(cmd, "kaideng"))
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        digitalWrite(LED, LOW);
    } else if(strcmp(cmd, "dadianhua") == 0)
    {
        printf("%s", cmd);
        cmd[0] = '\0';
        pubmsg.payload = "1";
        pubmsg.payloadlen = strlen("1");
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC_CALL, &pubmsg, &token);
        system("aplay -D default -f S16_LE -V mono -r8000 -c 2 -t wav zhengzaibotong.wav");
        call = 1;
    } else if(!strcmp(cmd, "jieting") && phone == 1)
    {
        printf("asfafsdafasd-----------------\n");
        pubmsg.payload = "1";
        pubmsg.payloadlen = strlen("1");
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC_ISPHONE, &pubmsg, &token);
        //system("firefox-esr file:///home/pi/Agora_/client/index.html");
        system("firefox-esr http://surine.cn/Agora_/client/");
        phone = 0;
    } else if(!strcmp(cmd, "guaduan") && phone == 1)
    {
        pubmsg.payload = "0";
        pubmsg.payloadlen = strlen("0");
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC_ISPHONE, &pubmsg, &token);
        phone = 0;
    }

    fflush (stdout) ;
}

