################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/main.c \
../Application/systick.c 

OBJS += \
./Application/main.o \
./Application/systick.o 

C_DEPS += \
./Application/main.d \
./Application/systick.d 


# Each subdirectory must supply rules for building sources it contributes
Application/%.o: ../Application/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"E:\gd32vf103\project\demo\Application" -I"E:\gd32vf103\project\demo\Peripherals" -I"E:\gd32vf103\project\demo\Peripherals\Include" -I"E:\gd32vf103\project\demo\Peripherals\Source" -I"E:\gd32vf103\project\demo\RISCV\stubs" -I"E:\gd32vf103\project\demo\RISCV\drivers" -I"E:\gd32vf103\project\demo\RISCV\env_Eclipse" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


