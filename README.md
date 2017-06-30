# cnsoftbei-raspberryPi
需要依赖MQTT, cJSON, wiringPi，语音识别使用串口模块，语音合成依赖迅飞TTS
## MQTT
```bash
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
make
sudo make install
```
## cJSON
```
git clone https://github.com/DaveGamble/cJSON.git
cd cJSON
mkdir build
cd build
cmake ..
```

