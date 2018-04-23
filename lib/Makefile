DEVICE := atmega328p
F_CPU  := 16000000

PROGRAMMER = arduino
SPEED  := 57600
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
PORT   := /dev/ttyUSB0
CC      := avr-gcc
AVRDUDE := avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(SPEED) -D -V
endif

ifeq ($(UNAME), Darwin)
PORT   := /dev/cu.wchusbserial1420
CC      := /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc
CONF 	:= /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf
AVRDUDE := /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C$(CONF) -v -p$(DEVICE) -c$(PROGRAMMER) -P$(PORT) -b$(SPEED) -D -V
endif

CFLAGS  += -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE)

OBJECTS := program.o
TMPOUT  := program.elf
OUT     := program.hex

LIB_PATH = lib_atmega328p
LIB_LINK = -L $(LIB_PATH) -l_atmega328p

all: $(OUT)

flash: all
	$(AVRDUDE) -U flash:w:program.hex:i

clean:
	-rm -f $(OUT) $(TMPOUT) $(OBJECTS)
	@make clean -C lib_atmega328p

$(OUT): $(OBJECTS)
	@make -C lib_atmega328p
	$(CC) $(CFLAGS) -o $(TMPOUT) $^ $(LIB_LINK)
	avr-objcopy -j .text -j .data -O ihex $(TMPOUT) $@
	avr-size --format=avr --mcu=$(DEVICE) $@
