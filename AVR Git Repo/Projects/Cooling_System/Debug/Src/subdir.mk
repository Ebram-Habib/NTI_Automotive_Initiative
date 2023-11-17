################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC_prog.c \
../Src/DCMOTOR_prog.c \
../Src/GIE_prog.c \
../Src/GPIO_prog.c \
../Src/LCD_prog.c \
../Src/LM35_SENSOR_prog.c \
../Src/TIMER0_prog.c \
../Src/app.c \
../Src/lcd.c 

OBJS += \
./Src/ADC_prog.o \
./Src/DCMOTOR_prog.o \
./Src/GIE_prog.o \
./Src/GPIO_prog.o \
./Src/LCD_prog.o \
./Src/LM35_SENSOR_prog.o \
./Src/TIMER0_prog.o \
./Src/app.o \
./Src/lcd.o 

C_DEPS += \
./Src/ADC_prog.d \
./Src/DCMOTOR_prog.d \
./Src/GIE_prog.d \
./Src/GPIO_prog.d \
./Src/LCD_prog.d \
./Src/LM35_SENSOR_prog.d \
./Src/TIMER0_prog.d \
./Src/app.d \
./Src/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


