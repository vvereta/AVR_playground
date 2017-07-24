F_CPU  := 16000000

#atmega2560
DEVICE := atmega2560
PROGRAMMER := wiring
PORT   := /dev/cu.usbmodem1421
SPEED  := 115200

#atmega328p
#DEVICE := atmega328p
#PROGRAMMER := arduino
#PORT   := /dev/cu.wchusbserial1420
#SPEED  := 57600

CC      := /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc
CONF 	:= /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf
AVRDUDE := /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C$(CONF) -v -p$(DEVICE) -c$(PROGRAMMER) -P$(PORT) -b$(SPEED) -D -V

CFLAGS  += -Wall -Os -DF_CPU=$(F_CPU) -DMCU=$(DEVICE) -mmcu=$(DEVICE)

OBJECTS := main.o 
TMPOUT  := main.elf
OUT     := main.hex

all: $(OUT)

flash: $(OUT)
	$(AVRDUDE) -U flash:w:$^:i

clean:
	-rm -f $(OUT) $(TMPOUT) $(OBJECTS)

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TMPOUT) $^
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -j .text -j .data -O ihex $(TMPOUT) $@
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-size --format=avr --mcu=$(DEVICE) $@

