################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./source/F2837xS_Adc.obj" \
"./source/F2837xS_CodeStartBranch.obj" \
"./source/F2837xS_CpuTimers.obj" \
"./source/F2837xS_DA.obj" \
"./source/F2837xS_DefaultISR.obj" \
"./source/F2837xS_EPwm.obj" \
"./source/F2837xS_GlobalVariableDefs.obj" \
"./source/F2837xS_Gpio.obj" \
"./source/F2837xS_PieCtrl.obj" \
"./source/F2837xS_PieVect.obj" \
"./source/F2837xS_Spi.obj" \
"./source/F2837xS_SysCtrl.obj" \
"./source/F2837xS_Xbar.obj" \
"./source/F2837xS_fault.obj" \
"./source/F2837xS_offset.obj" \
"./source/F2837xS_struct.obj" \
"./source/F2837xS_usDelay.obj" \
"./source/F2837xS_variable.obj" \
"./source/Filter.obj" \
"./source/RingBuff.obj" \
"./source/cc.obj" \
"./source/check_CRC.obj" \
"./source/easy2837xS_sci_v8.4.obj" \
"./source/main.obj" \
"../28377S_FLASH_lnk.cmd" \
"../cmd/F2837xS_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-lrts2800_fpu32.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include cmd/subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include cmd/subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Micro_INV.out \

EXE_OUTPUTS__QUOTED += \
"Micro_INV.out" \

BIN_OUTPUTS += \
Micro_INV.hex \

BIN_OUTPUTS__QUOTED += \
"Micro_INV.hex" \


# All Target
all: Micro_INV.out

# Tool invocations
Micro_INV.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --cla_support=cla1 --advice:performance=all --symdebug:coff --define=_FLASH --diag_wrap=off --diag_warning=225 --display_error_number -z -m"Micro_INV.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/lib" -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="Micro_INV_linkInfo.xml" --entry_point=code_start --rom_model -o "Micro_INV.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Micro_INV.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/bin/hex2000"  -o "Micro_INV.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "source\F2837xS_Adc.obj" "source\F2837xS_CodeStartBranch.obj" "source\F2837xS_CpuTimers.obj" "source\F2837xS_DA.obj" "source\F2837xS_DefaultISR.obj" "source\F2837xS_EPwm.obj" "source\F2837xS_GlobalVariableDefs.obj" "source\F2837xS_Gpio.obj" "source\F2837xS_PieCtrl.obj" "source\F2837xS_PieVect.obj" "source\F2837xS_Spi.obj" "source\F2837xS_SysCtrl.obj" "source\F2837xS_Xbar.obj" "source\F2837xS_fault.obj" "source\F2837xS_offset.obj" "source\F2837xS_struct.obj" "source\F2837xS_usDelay.obj" "source\F2837xS_variable.obj" "source\Filter.obj" "source\RingBuff.obj" "source\cc.obj" "source\check_CRC.obj" "source\easy2837xS_sci_v8.4.obj" "source\main.obj" 
	-$(RM) "source\F2837xS_Adc.d" "source\F2837xS_CpuTimers.d" "source\F2837xS_DA.d" "source\F2837xS_DefaultISR.d" "source\F2837xS_EPwm.d" "source\F2837xS_GlobalVariableDefs.d" "source\F2837xS_Gpio.d" "source\F2837xS_PieCtrl.d" "source\F2837xS_PieVect.d" "source\F2837xS_Spi.d" "source\F2837xS_SysCtrl.d" "source\F2837xS_Xbar.d" "source\F2837xS_fault.d" "source\F2837xS_offset.d" "source\F2837xS_struct.d" "source\F2837xS_variable.d" "source\Filter.d" "source\RingBuff.d" "source\cc.d" "source\check_CRC.d" "source\easy2837xS_sci_v8.4.d" "source\main.d" 
	-$(RM) "source\F2837xS_CodeStartBranch.d" "source\F2837xS_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

