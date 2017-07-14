DEVICE := atmega328p
F_CPU  := 16000000

PROGRAMMER = arduino
PORT   := /dev/ttyUSB0
SPEED  := 57600

CC      := avr-gcc
AVRDUDE := avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(SPEED) -D -V

CFLAGS  += -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE)

OBJECTS := main.o
TMPOUT  := main.elf
OUT     := main.hex

all: $(OUT)

flash: all
	$(AVRDUDE) -U flash:w:main.hex:i

clean:
	-rm -f $(OUT) $(TMPOUT) $(OBJECTS)

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TMPOUT) $^
	avr-objcopy -j .text -j .data -O ihex $(TMPOUT) $@
	avr-size --format=avr --mcu=$(DEVICE) $@

