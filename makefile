# Cross compiler name
CC = arm-none-eabi-gcc 
# Compiler flag or options
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 -Wall -o0
LDFLAGS = -T stm32_linker.ld -nostdlib -Wl,-Map=blinky.map

all: stm32_can.o stm32_gpio.o main.o stm32_startup.o blinky.bin
# target : dependency, $^ denotes dependency, $@ denotes target
stm32_gpio.o: stm32_gpio.c
	$(CC) $(CFLAGS) -o $@ $^
stm32_can.o: stm32_can.c
	$(CC) $(CFLAGS) -o $@ $^
stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^
main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^
blinky.elf: main.o stm32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^
blinky.bin: blinky.elf
	arm-none-eabi-objcopy -O binary $^ $@
clean:
	rm -rf *.o *.elf *.map *.bin