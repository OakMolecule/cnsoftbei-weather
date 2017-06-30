#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "mqtt.h"
#include "cJSON.h"
#include "remind.h"
#include "tts.h"
#include "num2cn.h"

volatile MQTTClient_deliveryToken deliveredtoken;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
MQTTClient_message pubmsg = MQTTClient_message_initializer;
MQTTClient_deliveryToken token;
MQTTClient client;
int remindSize;
int phone = 0;

struct remind* parseArray(char * pJson)
{
    if(NULL == pJson)
    {
        return NULL;
    }
    cJSON * root = NULL;
    if((root = cJSON_Parse(pJson)) == NULL)
    {
        return NULL;
    }
    int iSize = cJSON_GetArraySize(root);
    remindSize = iSize;
    struct remind *remindMes = (struct remind*)malloc(iSize * sizeof(struct remind));
    for(int iCnt = 0; iCnt < iSize; iCnt++)
    {
        cJSON * pSub = cJSON_GetArrayItem(root, iCnt);
        if(NULL == pSub)
        {
            continue;
        }
        cJSON * pSubSub = cJSON_GetObjectItem(pSub, "MedicineName");
        if(NULL == pSubSub)
        {
            // get object from subject object faild
        }
        strcpy(remindMes[iCnt].MedicineName, pSubSub->valuestring);
        printf("sub_obj_1 : %s\n", pSubSub->valuestring);

        pSubSub = cJSON_GetObjectItem(pSub, "Times");
        remindMes[iCnt].Times = pSubSub->valueint;
        printf("value[%2d] : [%d]\n", iCnt, remindMes[iCnt].Times);

        pSubSub = cJSON_GetObjectItem(pSub, "Amount");
        remindMes[iCnt].Amount = pSubSub->valueint;
        printf("value[%2d] : [%d]\n", iCnt, remindMes[iCnt].Amount);
    }   
    cJSON_Delete(root);
    return remindMes;
}

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;

}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;
    char json[100];
    struct remind* remindMes;

    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");

    payloadptr = message->payload;
    if(strcmp(topicName, TOPIC_PHONE) == 0)
    {
        if(*payloadptr == '1')
        {
            system("aplay -D default -f S16_LE -V mono -r8000 -c 2 -t wav dianhua.wav");
            phone = 1;
        }
    } else if (strcmp(topicName, TOPIC_ISCALL) == 0)
    {
        if (*payloadptr == '1' && call == 1)
        {
        //system("firefox-esr file:///home/pi/Agora_/client/index.html");
            system("firefox-esr http://surine.cn/Agora_/client/");
            call = 0;
        } else if(call == 1){
            system("aplay -D default -f S16_LE -V mono -r8000 -c 2 -t wav guaduan.wav");
            call = 0;
        }
    }

    for(i=0; i < message->payloadlen; i++)
    {
        json[i] = *payloadptr;
        putchar(*payloadptr++);
        json[i + 1] = '\0';
    }
    putchar('\n');

    printf("%s\n", json);
    remindMes = parseArray(json);
    printf("-------------%d-----------\n", remindSize);
    char text[100] = "";
    char amount[6];
    strcpy(text, "您该吃药了：");
    for(i = 0; i < remindSize; i++)
    {
        printf("%d\n", remindMes[i].Amount);
        num2cn(remindMes[i].Amount, amount);
        sprintf(text, "%s%s，%s粒。", text, (remindMes + i)->MedicineName, amount);
    }
    printf("%s", text);
    if(remindSize != 0)
        playMedcine(text);

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

int mqttInit()
{
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
            MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);

    }
    MQTTClient_subscribe(client, TOPIC_MID, QOS);
    MQTTClient_subscribe(client, TOPIC_PHONE, QOS);
    MQTTClient_subscribe(client, TOPIC_ISCALL, QOS);

    MQTTClient_publishMessage(client, TOPIC_TING, &pubmsg, &token);
    return rc;
}

