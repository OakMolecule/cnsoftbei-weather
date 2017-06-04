#include <stdio.h>
#include <string.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include "weather.h"
int parseJson(char * pMsg, struct weatherinfo * weather);

/*
 * 返回天气信息
 * cityid：中国天气网对应城市id
 * */
int getWeather(char * cityid, struct weatherinfo * weather)
{
    char buffer[300];
    char command[50];
    sprintf(command, "curl http://www.weather.com.cn/data/sk/%s.html", cityid);
    FILE * fp = popen(command, "r");
    fgets(buffer, sizeof(buffer), fp);
    pclose(fp);
    printf("%s\n", buffer);
    int err = parseJson(buffer, weather);
    if(err) {
        return err;
    }
    return 0;
}

int parseJson(char * pMsg, struct weatherinfo * weather)
{
    if(NULL == pMsg)
    {
        return 1;
    }
    cJSON * pJson = cJSON_Parse(pMsg);
    if(NULL == pJson) {
        // parse faild, return
        return 2;
    }

    // get string from json
    cJSON * pSub = cJSON_GetObjectItem(pJson, "weatherinfo");
    if(NULL == pSub) {
        //get object named "hello" faild
    }

    cJSON * pJsonWeather = cJSON_GetObjectItem(pSub, "city");
    strcpy(weather->city, pJsonWeather->valuestring);
    printf("%s\n", weather->city);

    pJsonWeather = cJSON_GetObjectItem(pSub, "cityid");
    strcpy(weather->cityid, pJsonWeather->valuestring);
    printf("%s\n", weather->cityid);

    pJsonWeather = cJSON_GetObjectItem(pSub, "temp");
    weather->temp = atoi(pJsonWeather->valuestring);
    printf("%d\n", weather->temp);

    pJsonWeather = cJSON_GetObjectItem(pSub, "WD");
    strcpy(weather->wd, pJsonWeather->valuestring);
    printf("%s\n", weather->wd);

    pJsonWeather = cJSON_GetObjectItem(pSub, "WS");
    weather->ws = atoi(pJsonWeather->valuestring);
    printf("%d\n", weather->ws);

    cJSON_Delete(pJson);
    return 0;
}

