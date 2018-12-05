################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/adc.obj: ../Source/adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/adc.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/clk.obj: ../Source/clk.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/clk.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/cpu.obj: ../Source/cpu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/cpu.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/f2802x_defaultisr.obj: ../Source/f2802x_defaultisr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/f2802x_defaultisr.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/flash.obj: ../Source/flash.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/flash.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/gpio.obj: ../Source/gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/gpio.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/pie.obj: ../Source/pie.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/pie.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/pll.obj: ../Source/pll.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/pll.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/pwm.obj: ../Source/pwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/pwm.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/timer.obj: ../Source/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/timer.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/wdog.obj: ../Source/wdog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization" --include_path="C:/Users/Curtis/Documents/Sustaingineering/MPPT/Firmware/Curtis/ParticleSwarmOptimization/Headers" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=_DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/wdog.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


