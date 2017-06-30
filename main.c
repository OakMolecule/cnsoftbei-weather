#include "mqtt.h"
#include "weather.h"
#include "serial.h"
#include "tts.h"

int main()
{
    int fd;
    fd = initSerial("/dev/ttyUSB0", 9600);
    mqttInit();
    xunfeiInit();

    while (1)
    {
        readSerial(fd);
    }

    xunfeiLogout();
}

