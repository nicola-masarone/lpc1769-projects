################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/lpc1769.c \
../src/sysinit.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/lpc1769.o \
./src/sysinit.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/lpc1769.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"/media/data/Documenti/Scuola/anno scolastico 2014-2015/workspace-LPCXpresso/lpc_board_nxp_lpcxpresso_1769/inc" -I"/media/data/Documenti/Scuola/anno scolastico 2014-2015/workspace-LPCXpresso/lpc_chip_175x_6x/inc" -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


