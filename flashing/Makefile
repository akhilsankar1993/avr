#!/usr/bin/make
# -*- makefile -*-

#    Copyright (C) 2008  Daniel Richman
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    For a full copy of the GNU General Public License, 
#    see <http://www.gnu.org/licenses/>.

F_CPU = 1000000UL
mmcu = atmega168
port = /dev/cu.usbmodem14511
controller = avrisp
baud = 19200

cfiles   := $(wildcard *.c)
hexfiles := $(patsubst %.c,%.hex,$(cfiles))

avr_gcc = avr-gcc
avr_objcopy = avr-objcopy
avr_size = avr-size
avrdude = avrdude

CFLAGS   = -mmcu=$(mmcu) -DF_CPU=$(F_CPU) -pipe -Wall -O2
MAPFLAGS = -Wl,-Map,

all : $(hexfiles)

%.elf : %.c
	$(avr_gcc)  $(CFLAGS) -o $@ $<
	$(avr_size) --common $@

%.hex : %.elf
	$(avr_objcopy) -O ihex $< $@

# avrdude -c avrisp -p m168 -P /dev/cu.usbmodem14511 -b 19200 -U flash:w:blinkLED.hex

%.hex.upload : %.hex
	$(avrdude) -c $(controller) -p $(mmcu) -P $(port) -b $(baud) -U flash:w:$<

clean :
	rm -f *.hex 

.PHONY : clean
.DEFAULT_GOAL := all