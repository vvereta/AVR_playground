DEVICE := atmega328p
F_CPU  := 16000000

PROGRAMMER = arduino
SPEED  := 57600
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
PORT   := /dev/ttyUSB1
CC      := avr-gcc
AVRDUDE := avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(SPEED) -D -V
endif

ifeq ($(UNAME), Darwin)
PORT	:= /dev/cu.wchusbserial1420
CC		:= /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-gcc
CONF 	:= /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf
AVRDUDE := /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C$(CONF) -v -p$(DEVICE) -c$(PROGRAMMER) -P$(PORT) -b$(SPEED) -D -V
endif

CFLAGS  += -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE)

#FOLDERS
SOURCES_FLD = src
INCLUDES_FLD = inc
OBJECTS_FLD = obj
ELF_FLD = elf

#FILES
OBJECTS = \
	 $(OBJECTS_FLD)/program.o \
	 $(OBJECTS_FLD)/foo.o \

TMPOUT	= \
	$(ELF_FLD)/program.elf

OUT		= program.hex

LIB_PATH = lib_atmega328p
LIB_LINK = -L $(LIB_PATH) -l_atmega328p

all: $(OUT)

flash: all
	$(AVRDUDE) -U flash:w:program.hex:i

clean:
	@rm -rf $(OBJECTS_FLD)
	@rm -rf $(ELF_FLD)
	@echo "\033[33m Cleaning .o files of $(OUT) \033[0m"
	@make clean -C lib_atmega328p

fclean: clean
	@rm -f $(OUT)
	@echo "\033[31m Binary $(OUT) deleted \033[0m"
	@make fclean -C lib_atmega328p

$(OUT): $(OBJECTS)
	@make -C lib_atmega328p
	@$(CC) -I $(INCLUDES_FLD) $(CFLAGS) $(OBJECTS)-o $(TMPOUT) $(LIB_LINK)
	@avr-objcopy -j .text -j .data -O ihex $(TMPOUT) $@
	@avr-size --format=avr --mcu=$(DEVICE) $@
	@echo "\033[32m $(OUT) was created \033[0m"

$(OBJECTS_FLD)/program.o : $(SOURCES_FLD)/program.c
	@mkdir -p $(OBJECTS_FLD)
	@mkdir -p $(ELF_FLD)
	@$(CC) -I $(INCLUDES_FLD) $(CFLAGS) -c $(SOURCES_FLD)/program.c -o $(OBJECTS_FLD)/program.o

$(OBJECTS_FLD)/foo.o : $(SOURCES_FLD)/foo.c
	@$(CC) -I $(INCLUDES_FLD) $(CFLAGS) -c $(SOURCES_FLD)/foo.c -o $(OBJECTS_FLD)/foo.o
