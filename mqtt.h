#ifndef __MQTT_H
#define __MQTT_H

#include "MQTTClient.h"

#define ADDRESS         "tcp://iot.celitea.cn:1883"
#define CLIENTID        "ExampleClientSub"
#define TOPIC_MID       "/raspberry/medicine"
#define TOPIC_PHONE     "/raspberry/phone"
#define TOPIC_ISPHONE   "/raspberry/isphone"
#define TOPIC_CALL      "/raspberry/call"
#define TOPIC_ISCALL    "/raspberry/iscall"
#define TOPIC_TING      "inTopic"
#define PAYLOAD         "Hello World!"
#define QOS             1
#define TIMEOUT         10000L

extern MQTTClient_connectOptions conn_opts;
extern MQTTClient_message pubmsg;
extern MQTTClient client;
extern MQTTClient_deliveryToken token;
extern int phone;
extern int call;

int mqttInit();

#endif
