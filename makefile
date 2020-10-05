# Cross compiler name
CC = arm-none-eabi-gcc 
# Compiler flag or options
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 -Wall -o0
LDFLAGS = -T stm32_linker.ld -nostdlib -Wl,-Map=final.map

all: stm32_can.o stm32_gpio.o main.o stm32_startup.o final.bin
# target : dependency, $^ denotes dependency, $@ denotes target
stm32_gpio.o: stm32_gpio.c
	$(CC) $(CFLAGS) -o $@ $^
stm32_can.o: stm32_can.c
	$(CC) $(CFLAGS) -o $@ $^
system_stm32f10x.o: system_stm32f10x.c
	$(CC) $(CFLAGS) -o $@ $^
stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^
main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^
final.elf: main.o stm32_startup.o stm32_gpio.o stm32_can.o system_stm32f10x.o
	$(CC) $(LDFLAGS) -o $@ $^
final.bin: final.elf
	arm-none-eabi-objcopy -O binary $^ $@
clean:
	rm -rf *.o *.elf *.map *.bin