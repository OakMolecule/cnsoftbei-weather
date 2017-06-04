#ifndef __WEATHER_H
#define __WEATHER_H

struct weatherinfo {
    char city[20];
    char cityid[12];
    int temp;
    char wd[10];
    int ws;
    char sd[4];
};

int getWeather(char* , struct weatherinfo*);

#endif
