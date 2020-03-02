################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
source/F2837xS_Adc.obj: ../source/F2837xS_Adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_Adc.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_CodeStartBranch.obj: ../source/F2837xS_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_CodeStartBranch.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_CpuTimers.obj: ../source/F2837xS_CpuTimers.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_CpuTimers.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_DA.obj: ../source/F2837xS_DA.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_DA.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_DefaultISR.obj: ../source/F2837xS_DefaultISR.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_DefaultISR.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_EPwm.obj: ../source/F2837xS_EPwm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_EPwm.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_GlobalVariableDefs.obj: ../source/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_GlobalVariableDefs.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_Gpio.obj: ../source/F2837xS_Gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_Gpio.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_PieCtrl.obj: ../source/F2837xS_PieCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_PieCtrl.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_PieVect.obj: ../source/F2837xS_PieVect.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_PieVect.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_Spi.obj: ../source/F2837xS_Spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_Spi.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_SysCtrl.obj: ../source/F2837xS_SysCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_SysCtrl.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_Xbar.obj: ../source/F2837xS_Xbar.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_Xbar.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_fault.obj: ../source/F2837xS_fault.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_fault.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_offset.obj: ../source/F2837xS_offset.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_offset.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_struct.obj: ../source/F2837xS_struct.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_struct.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_usDelay.obj: ../source/F2837xS_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_usDelay.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/F2837xS_variable.obj: ../source/F2837xS_variable.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/F2837xS_variable.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/Filter.obj: ../source/Filter.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/Filter.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/RingBuff.obj: ../source/RingBuff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/RingBuff.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/cc.obj: ../source/cc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/cc.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/easy2837xS_sci_v8.4.obj: ../source/easy2837xS_sci_v8.4.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/easy2837xS_sci_v8.4.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/main.obj: ../source/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c2000_6.4.11/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 --include_path="C:/KMPlayer/code/2018_01_19/INV/28377S_POWER/include" --include_path="C:/ti/ccsv6/tools/compiler/c2000_6.4.11/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_common/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v150/F2837xS_headers/include" --advice:performance=all --symdebug:coff --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/main.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


