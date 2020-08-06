################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../source/F2837xS_CodeStartBranch.asm \
../source/F2837xS_usDelay.asm 

C_SRCS += \
../source/F2837xS_Adc.c \
../source/F2837xS_CpuTimers.c \
../source/F2837xS_DA.c \
../source/F2837xS_DefaultISR.c \
../source/F2837xS_EPwm.c \
../source/F2837xS_GlobalVariableDefs.c \
../source/F2837xS_Gpio.c \
../source/F2837xS_PieCtrl.c \
../source/F2837xS_PieVect.c \
../source/F2837xS_Spi.c \
../source/F2837xS_SysCtrl.c \
../source/F2837xS_Xbar.c \
../source/F2837xS_fault.c \
../source/F2837xS_offset.c \
../source/F2837xS_struct.c \
../source/F2837xS_variable.c \
../source/Filter.c \
../source/RingBuff.c \
../source/cc.c \
../source/easy2837xS_sci_v8.4.c \
../source/main.c 

C_DEPS += \
./source/F2837xS_Adc.d \
./source/F2837xS_CpuTimers.d \
./source/F2837xS_DA.d \
./source/F2837xS_DefaultISR.d \
./source/F2837xS_EPwm.d \
./source/F2837xS_GlobalVariableDefs.d \
./source/F2837xS_Gpio.d \
./source/F2837xS_PieCtrl.d \
./source/F2837xS_PieVect.d \
./source/F2837xS_Spi.d \
./source/F2837xS_SysCtrl.d \
./source/F2837xS_Xbar.d \
./source/F2837xS_fault.d \
./source/F2837xS_offset.d \
./source/F2837xS_struct.d \
./source/F2837xS_variable.d \
./source/Filter.d \
./source/RingBuff.d \
./source/cc.d \
./source/easy2837xS_sci_v8.4.d \
./source/main.d 

OBJS += \
./source/F2837xS_Adc.obj \
./source/F2837xS_CodeStartBranch.obj \
./source/F2837xS_CpuTimers.obj \
./source/F2837xS_DA.obj \
./source/F2837xS_DefaultISR.obj \
./source/F2837xS_EPwm.obj \
./source/F2837xS_GlobalVariableDefs.obj \
./source/F2837xS_Gpio.obj \
./source/F2837xS_PieCtrl.obj \
./source/F2837xS_PieVect.obj \
./source/F2837xS_Spi.obj \
./source/F2837xS_SysCtrl.obj \
./source/F2837xS_Xbar.obj \
./source/F2837xS_fault.obj \
./source/F2837xS_offset.obj \
./source/F2837xS_struct.obj \
./source/F2837xS_usDelay.obj \
./source/F2837xS_variable.obj \
./source/Filter.obj \
./source/RingBuff.obj \
./source/cc.obj \
./source/easy2837xS_sci_v8.4.obj \
./source/main.obj 

ASM_DEPS += \
./source/F2837xS_CodeStartBranch.d \
./source/F2837xS_usDelay.d 

OBJS__QUOTED += \
"source\F2837xS_Adc.obj" \
"source\F2837xS_CodeStartBranch.obj" \
"source\F2837xS_CpuTimers.obj" \
"source\F2837xS_DA.obj" \
"source\F2837xS_DefaultISR.obj" \
"source\F2837xS_EPwm.obj" \
"source\F2837xS_GlobalVariableDefs.obj" \
"source\F2837xS_Gpio.obj" \
"source\F2837xS_PieCtrl.obj" \
"source\F2837xS_PieVect.obj" \
"source\F2837xS_Spi.obj" \
"source\F2837xS_SysCtrl.obj" \
"source\F2837xS_Xbar.obj" \
"source\F2837xS_fault.obj" \
"source\F2837xS_offset.obj" \
"source\F2837xS_struct.obj" \
"source\F2837xS_usDelay.obj" \
"source\F2837xS_variable.obj" \
"source\Filter.obj" \
"source\RingBuff.obj" \
"source\cc.obj" \
"source\easy2837xS_sci_v8.4.obj" \
"source\main.obj" 

C_DEPS__QUOTED += \
"source\F2837xS_Adc.d" \
"source\F2837xS_CpuTimers.d" \
"source\F2837xS_DA.d" \
"source\F2837xS_DefaultISR.d" \
"source\F2837xS_EPwm.d" \
"source\F2837xS_GlobalVariableDefs.d" \
"source\F2837xS_Gpio.d" \
"source\F2837xS_PieCtrl.d" \
"source\F2837xS_PieVect.d" \
"source\F2837xS_Spi.d" \
"source\F2837xS_SysCtrl.d" \
"source\F2837xS_Xbar.d" \
"source\F2837xS_fault.d" \
"source\F2837xS_offset.d" \
"source\F2837xS_struct.d" \
"source\F2837xS_variable.d" \
"source\Filter.d" \
"source\RingBuff.d" \
"source\cc.d" \
"source\easy2837xS_sci_v8.4.d" \
"source\main.d" 

ASM_DEPS__QUOTED += \
"source\F2837xS_CodeStartBranch.d" \
"source\F2837xS_usDelay.d" 

C_SRCS__QUOTED += \
"../source/F2837xS_Adc.c" \
"../source/F2837xS_CpuTimers.c" \
"../source/F2837xS_DA.c" \
"../source/F2837xS_DefaultISR.c" \
"../source/F2837xS_EPwm.c" \
"../source/F2837xS_GlobalVariableDefs.c" \
"../source/F2837xS_Gpio.c" \
"../source/F2837xS_PieCtrl.c" \
"../source/F2837xS_PieVect.c" \
"../source/F2837xS_Spi.c" \
"../source/F2837xS_SysCtrl.c" \
"../source/F2837xS_Xbar.c" \
"../source/F2837xS_fault.c" \
"../source/F2837xS_offset.c" \
"../source/F2837xS_struct.c" \
"../source/F2837xS_variable.c" \
"../source/Filter.c" \
"../source/RingBuff.c" \
"../source/cc.c" \
"../source/easy2837xS_sci_v8.4.c" \
"../source/main.c" 

ASM_SRCS__QUOTED += \
"../source/F2837xS_CodeStartBranch.asm" \
"../source/F2837xS_usDelay.asm" 


