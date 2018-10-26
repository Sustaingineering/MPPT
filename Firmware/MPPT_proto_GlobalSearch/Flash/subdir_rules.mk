################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x/common/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x/headers/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/libraries/math/IQmath/c28/include" --define=_DEBUG --define=_FLASH --define=LARGE_MODEL -g --diag_suppress=232 --diag_suppress=10063 --diag_warning=225 --verbose_diagnostics --quiet --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

mppt.obj: ../mppt.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x/common/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x/headers/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/libraries/math/IQmath/c28/include" --define=_DEBUG --define=_FLASH --define=LARGE_MODEL -g --diag_suppress=232 --diag_suppress=10063 --diag_warning=225 --verbose_diagnostics --quiet --preproc_with_compile --preproc_dependency="mppt.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors.obj: ../sensors.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x/common/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x/headers/include" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/device_support/f2802x" --include_path="C:/ti/C2000Ware_1_00_04_00_Software/libraries/math/IQmath/c28/include" --define=_DEBUG --define=_FLASH --define=LARGE_MODEL -g --diag_suppress=232 --diag_suppress=10063 --diag_warning=225 --verbose_diagnostics --quiet --preproc_with_compile --preproc_dependency="sensors.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


