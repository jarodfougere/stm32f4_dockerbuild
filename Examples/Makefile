CC=arm-none-eabi-gcc
LD=arm-none-eabi-LD
CP=arm-none-eabi-objcopy

LINKER_SCRIPT=linker.ld

CFLAGS = -c -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LFLAGS = -nostartfiles -T$(LINKER_SCRIPT)
CPFLAG = -Obinary

all: main.bin

main.o: main.c
    $(CC) $(CFLAGS) -o main.o main.c

main.elf: main.o
    $(LD) $(LFLAGS) -o main.elf main.o

main.bin: main.elf
    $(CP) $(CPFLAGS) main.elf main.bin

clean:
    rm -rf *.o *.elf *.bin

write: 
    ./write_bin.sh openocd.cfg main.elf

