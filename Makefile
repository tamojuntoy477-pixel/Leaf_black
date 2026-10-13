# Leaf Black — GBA homebrew prototype
DEVKITPRO ?= /opt/devkitpro
DEVKITARM ?= $(DEVKITPRO)/devkitARM
CC := $(DEVKITARM)/bin/arm-none-eabi-gcc
OBJCOPY := $(DEVKITARM)/bin/arm-none-eabi-objcopy
ARCH := -mthumb -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi
CFLAGS := -g -Wall -O2 $(ARCH) -I$(DEVKITPRO)/libgba/include
LDFLAGS := -g $(ARCH) -specs=gba.specs -Wl,-Map,leafblack.map
LIBS := -L$(DEVKITPRO)/libgba/lib -lgba
TARGET := leafblack
OBJS := src/main.o

.PHONY: all clean
all: $(TARGET).gba
src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@
$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@
$(TARGET).gba: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).gba leafblack.map
