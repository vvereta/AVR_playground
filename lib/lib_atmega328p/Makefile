NAME = lib_atmega328p.a

CC = avr-gcc

DEVICE := atmega328p
F_CPU  := 16000000

CFLAGS  += -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE)

SOURCES_FLD = src

INCLUDES_FLD = inc

OBJECTS_FLD = obj

OBJECTS =\
	$(OBJECTS_FLD)/add.o\

INCLUDES =\
	$(INCLUDES_FLD)/lib_atmega328p.h


all : $(NAME)

$(NAME) : $(OBJECTS) $(INCLUDES)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "\033[32m $(NAME) was created \033[0m"

clean :
	@rm -f $(OBJECTS)
	@rm -rf $(OBJECTS_FLD)
	@echo "\033[33m Cleaning .o files of $(NAME) \033[0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[31m Binary $(NAME) deleted \033[0m"

re : fclean all

$(OBJECTS_FLD)/add.o : $(SOURCES_FLD)/add.c
	@mkdir -p $(OBJECTS_FLD)
	@$(CC) -I $(INCLUDES_FLD) $(CFLAGS) -c $(SOURCES_FLD)/add.c -o $(OBJECTS_FLD)/add.o
