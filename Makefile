# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for game

# Definitions
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm

# Source files
# Do not include header files here if they do not have an implementation
# as they will be injected into the using class if they are using and
# will cause make to fail.
SRC = game.c \
      ../../drivers/button.c \
      ../../drivers/avr/ir_uart.c \
      ../../drivers/avr/pio.c \
      ../../drivers/avr/prescale.c \
      ../../drivers/avr/system.c \
      ../../drivers/avr/timer.c \
      ../../drivers/avr/timer0.c \
      ../../drivers/avr/usart1.c \
      ../../drivers/display.c \
      ../../drivers/ledmat.c \
      ../../drivers/navswitch.c \
      ../../utils/font.c \
      ../../utils/pacer.c \
      ../../utils/tinygl.c \
      ../../drivers/led.c \
      navigation_switch.c \
      player_management.c \
      board.c \
      message.c \
      ir.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: game.out

# Found on github, an easier way to compile a bunch of source files
# Compile: create object files from C source files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files
game.out: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Target: clean project
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex

# Target: program project
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
