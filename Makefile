IDIR=Application/Core/Inc Application/Port/Inc Drivers/CMSIS/Core/Include Drivers/CMSIS/Device/ST/STM32F3xx Drivers/CMSIS/Include Drivers/ Middleware/ Middleware/Inc/


csrc = $(wildcard Application/Port/*.c) \
	   $(wildcard Application/Core/*.c) \
	   $(wildcard Middleware/Src/*.c)   \
	   $(wildcard Drivers/Peripherals/Src/*.c)
obj = $(csrc:.c=.o)


mygame: $(obj)
	$(CC) -o $@ $^ -I Application/Core/Inc -I Application/Port/Inc -I Drivers/-I CMSIS/Core/Include -I Drivers/CMSIS/Device/ST/STM32F3xx -I Drivers/CMSIS/Include -I Drivers/ -I Middleware/ -I Middleware/Inc/