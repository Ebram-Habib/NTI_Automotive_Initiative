################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO_Cfg.c \
../GPIO_Int.c \
../KeyPad.c \
../LCD_prog.c \
../main.c 

OBJS += \
./GPIO_Cfg.o \
./GPIO_Int.o \
./KeyPad.o \
./LCD_prog.o \
./main.o 

C_DEPS += \
./GPIO_Cfg.d \
./GPIO_Int.d \
./KeyPad.d \
./LCD_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


