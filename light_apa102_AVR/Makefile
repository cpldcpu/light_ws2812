# Makefile to build light_apa102 library examples
# This is not a very good example of a makefile - the dependencies do not work, therefore everything is rebuilt every time.

# Change these parameters for your device

F_CPU = 16000000
DEVICE = attiny85

# Tools:
CC = avr-gcc

LIB       = light_apa102
EXAMPLES  = RGB_blinky 
DEP		  = apa102_config.h Light_apa102/light_apa102.h

CFLAGS = -g2 -I. -ILight_apa102 -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) 
CFLAGS+= -Os -ffunction-sections -fdata-sections -fpack-struct -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions  
CFLAGS+= -Wall -Wno-pointer-to-int-cast
#CFLAGS+= -Wa,-ahls=$<.lst

LDFLAGS = -Wl,--relax,--section-start=.text=0,-Map=main.map

all:	$(EXAMPLES) 

$(LIB): $(DEP)
	@echo Building Library 
	@$(CC) $(CFLAGS) -o Objects/$@.o -c Light_apa102/$@.c 

$(EXAMPLES): $(LIB) 
	@echo Building $@
	@$(CC) $(CFLAGS) -o Objects/$@.o Examples/$@.c Light_apa102/$^.c
	@avr-size Objects/$@.o
	@avr-objcopy -j .text  -j .data -O ihex Objects/$@.o $@.hex
	@avr-objdump -d -S Objects/$@.o >Objects/$@.lss

.PHONY:	clean

clean:
	rm -f *.hex Objects/*.o Objects/*.lss
