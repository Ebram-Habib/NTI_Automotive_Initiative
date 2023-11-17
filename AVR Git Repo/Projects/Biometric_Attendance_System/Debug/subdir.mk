################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FingerPS_prog.c \
../GIE_prog.c \
../GPIO_prog.c \
../KeyPad.c \
../LCD_prog.c \
../TIMER0_prog.c \
../UART_prog.c \
../main.c 

OBJS += \
./FingerPS_prog.o \
./GIE_prog.o \
./GPIO_prog.o \
./KeyPad.o \
./LCD_prog.o \
./TIMER0_prog.o \
./UART_prog.o \
./main.o 

C_DEPS += \
./FingerPS_prog.d \
./GIE_prog.d \
./GPIO_prog.d \
./KeyPad.d \
./LCD_prog.d \
./TIMER0_prog.d \
./UART_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


