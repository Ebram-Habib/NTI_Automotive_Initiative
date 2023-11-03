################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GIE_prog.c \
../GPIO_Cfg.c \
../GPIO_Int.c \
../TIMER1_prog.c \
../main.c 

OBJS += \
./GIE_prog.o \
./GPIO_Cfg.o \
./GPIO_Int.o \
./TIMER1_prog.o \
./main.o 

C_DEPS += \
./GIE_prog.d \
./GPIO_Cfg.d \
./GPIO_Int.d \
./TIMER1_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


