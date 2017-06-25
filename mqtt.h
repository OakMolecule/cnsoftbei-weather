#ifndef __MQTT_H
#define __MQTT_H

#include "MQTTClient.h"

#define ADDRESS     "tcp://iot.celitea.cn:1883"
#define CLIENTID    "ExampleClientSub"
#define TOPIC_MID   "/raspberry/medicine"
#define TOPIC_TING  "inTopic"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

extern MQTTClient_connectOptions conn_opts;
extern MQTTClient_message pubmsg;
extern MQTTClient client;
extern MQTTClient_deliveryToken token;

int mqttInit();

#endif
