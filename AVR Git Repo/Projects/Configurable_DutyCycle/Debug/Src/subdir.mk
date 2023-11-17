################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GIE_prog.c \
../Src/GPIO_prog.c \
../Src/KeyPad.c \
../Src/LCD_prog.c \
../Src/TIMER0_prog.c \
../Src/TIMER1_prog.c \
../Src/app.c 

OBJS += \
./Src/GIE_prog.o \
./Src/GPIO_prog.o \
./Src/KeyPad.o \
./Src/LCD_prog.o \
./Src/TIMER0_prog.o \
./Src/TIMER1_prog.o \
./Src/app.o 

C_DEPS += \
./Src/GIE_prog.d \
./Src/GPIO_prog.d \
./Src/KeyPad.d \
./Src/LCD_prog.d \
./Src/TIMER0_prog.d \
./Src/TIMER1_prog.d \
./Src/app.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


