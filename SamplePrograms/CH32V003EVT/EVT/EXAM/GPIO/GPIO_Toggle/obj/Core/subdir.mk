################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Admin/Downloads/WCH\ -\ CH32V003/CH32V003EVT/EVT/EXAM/SRC/Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/core_riscv.o: C:/Users/Admin/Downloads/WCH\ -\ CH32V003/CH32V003EVT/EVT/EXAM/SRC/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Admin\Downloads\WCH - CH32V003\CH32V003EVT\EVT\EXAM\SRC\Debug" -I"C:\Users\Admin\Downloads\WCH - CH32V003\CH32V003EVT\EVT\EXAM\SRC\Core" -I"C:\Users\Admin\Downloads\WCH - CH32V003\CH32V003EVT\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"C:\Users\Admin\Downloads\WCH - CH32V003\CH32V003EVT\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

