################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/%.obj: ../source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --cla_support=cla1 --include_path="C:/Users/User/Desktop/micro_robot_app/code/Micro_INV/include" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --define=_FLASH --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/%.obj: ../source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --cla_support=cla1 --include_path="C:/Users/User/Desktop/micro_robot_app/code/Micro_INV/include" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_15.12.6.LTS/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --define=_FLASH --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


