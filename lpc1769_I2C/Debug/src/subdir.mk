################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/i2c.c \
../src/lpc1769.c \
../src/sysinit.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/i2c.o \
./src/lpc1769.o \
./src/sysinit.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/i2c.d \
./src/lpc1769.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"/home/nicola/MCUXpressoWorkSpace/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/nicola/MCUXpressoWorkSpace/lpc_chip_175x_6x/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


