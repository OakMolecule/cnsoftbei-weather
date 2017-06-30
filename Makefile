#common makefile header

DIR_INC = ../../include -I./
#DIR_BIN = ../../bin
DIR_BIN = ./
DIR_LIB = /usr/local/lib -L../../libs

TARGET	= tts_sample
BIN_TARGET = $(DIR_BIN)/$(TARGET)

CROSS_COMPILE = 
CFLAGS = -g -Wall -lwiringPi -I$(DIR_INC)

LDFLAGS := -L$(DIR_LIB)/RaspberryPi
LDFLAGS += -lmsc -lrt -ldl -lpthread

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

$(BIN_TARGET) : $(OBJECTS)
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CROSS_COMPILE)gcc -c -std=gnu99 $(CFLAGS) $< -o $@
clean:
	@rm -f *.o $(BIN_TARGET)

.PHONY:clean

#common makefile foot
