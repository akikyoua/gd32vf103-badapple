################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/fatfs/ff.c \
../Application/fatfs/ffsystem.c \
../Application/fatfs/ffunicode.c \
../Application/fatfs/tf_card.c 

OBJS += \
./Application/fatfs/ff.o \
./Application/fatfs/ffsystem.o \
./Application/fatfs/ffunicode.o \
./Application/fatfs/tf_card.o 

C_DEPS += \
./Application/fatfs/ff.d \
./Application/fatfs/ffsystem.d \
./Application/fatfs/ffunicode.d \
./Application/fatfs/tf_card.d 


# Each subdirectory must supply rules for building sources it contributes
Application/fatfs/%.o: ../Application/fatfs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"E:\gd32vf103\project\demo\Application" -I"E:\gd32vf103\project\demo\Peripherals" -I"E:\gd32vf103\project\demo\Peripherals\Include" -I"E:\gd32vf103\project\demo\Peripherals\Source" -I"E:\gd32vf103\project\demo\RISCV\stubs" -I"E:\gd32vf103\project\demo\RISCV\drivers" -I"E:\gd32vf103\project\demo\RISCV\env_Eclipse" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


