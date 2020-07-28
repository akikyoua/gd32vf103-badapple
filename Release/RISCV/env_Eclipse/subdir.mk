################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RISCV/env_Eclipse/handlers.c \
../RISCV/env_Eclipse/init.c \
../RISCV/env_Eclipse/your_printf.c 

S_UPPER_SRCS += \
../RISCV/env_Eclipse/entry.S \
../RISCV/env_Eclipse/start.S 

OBJS += \
./RISCV/env_Eclipse/entry.o \
./RISCV/env_Eclipse/handlers.o \
./RISCV/env_Eclipse/init.o \
./RISCV/env_Eclipse/start.o \
./RISCV/env_Eclipse/your_printf.o 

S_UPPER_DEPS += \
./RISCV/env_Eclipse/entry.d \
./RISCV/env_Eclipse/start.d 

C_DEPS += \
./RISCV/env_Eclipse/handlers.d \
./RISCV/env_Eclipse/init.d \
./RISCV/env_Eclipse/your_printf.d 


# Each subdirectory must supply rules for building sources it contributes
RISCV/env_Eclipse/%.o: ../RISCV/env_Eclipse/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -x assembler-with-cpp -I"E:\gd32vf103\project\demo\Application" -I"E:\gd32vf103\project\demo\Peripherals" -I"E:\gd32vf103\project\demo\Peripherals\Include" -I"E:\gd32vf103\project\demo\Peripherals\Source" -I"E:\gd32vf103\project\demo\RISCV\stubs" -I"E:\gd32vf103\project\demo\RISCV\drivers" -I"E:\gd32vf103\project\demo\RISCV\env_Eclipse" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RISCV/env_Eclipse/%.o: ../RISCV/env_Eclipse/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"E:\gd32vf103\project\demo\Application" -I"E:\gd32vf103\project\demo\Peripherals" -I"E:\gd32vf103\project\demo\Peripherals\Include" -I"E:\gd32vf103\project\demo\Peripherals\Source" -I"E:\gd32vf103\project\demo\RISCV\stubs" -I"E:\gd32vf103\project\demo\RISCV\drivers" -I"E:\gd32vf103\project\demo\RISCV\env_Eclipse" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


