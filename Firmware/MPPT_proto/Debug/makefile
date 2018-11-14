################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./adc.obj" \
"./cap.obj" \
"./clk.obj" \
"./cpu.obj" \
"./f2802x_comp.obj" \
"./f2802x_cputimers.obj" \
"./f2802x_defaultisr.obj" \
"./f2802x_ecap.obj" \
"./f2802x_gpio.obj" \
"./f2802x_piectrl.obj" \
"./f2802x_pievect.obj" \
"./f2802x_sci.obj" \
"./f2802x_sysctrl.obj" \
"./flash.obj" \
"./gpio.obj" \
"./main.obj" \
"./mppt.obj" \
"./pie.obj" \
"./pll.obj" \
"./pwm.obj" \
"./sci.obj" \
"./sci_io.obj" \
"./sensors.obj" \
"./timer.obj" \
"./wdog.obj" \
"../F28023.cmd" \
"../F2802x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/lib/rts2800_ml.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include RAM/subdir_vars.mk
-include subdir_rules.mk
-include RAM/subdir_rules.mk
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
MPPT_Proto.out \

EXE_OUTPUTS__QUOTED += \
"MPPT_Proto.out" \

BIN_OUTPUTS += \
MPPT_Proto.hex \

BIN_OUTPUTS__QUOTED += \
"MPPT_Proto.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "MPPT_Proto.out"

# Tool invocations
MPPT_Proto.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/cl2000" -v28 -ml -mt --advice:performance=all --define=_DEBUG --define=_FLASH --define=LARGE_MODEL -g --diag_suppress=232 --diag_suppress=10063 --diag_warning=225 --verbose_diagnostics --quiet -z -m"MPPT_Particle_Swarm.map" --stack_size=0x200 --warn_sections -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/lib" -i"C:/Users/OneTi/MPPT/MPPT_Proto" -i"C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2802x" -i"C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2802x/common/header" -i"C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2802x/common/lib" -i"C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2802x/common/source" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/include" --reread_libs --display_error_number --issue_remarks --verbose_diagnostics --xml_link_info="MPPT_Particle_Swarm.xml" --entry_point=_c_int00 --rom_model -o "MPPT_Proto.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

MPPT_Proto.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.3.LTS/bin/hex2000"  -o "MPPT_Proto.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "adc.obj" "cap.obj" "clk.obj" "cpu.obj" "f2802x_comp.obj" "f2802x_cputimers.obj" "f2802x_defaultisr.obj" "f2802x_ecap.obj" "f2802x_gpio.obj" "f2802x_piectrl.obj" "f2802x_pievect.obj" "f2802x_sci.obj" "f2802x_sysctrl.obj" "flash.obj" "gpio.obj" "main.obj" "mppt.obj" "pie.obj" "pll.obj" "pwm.obj" "sci.obj" "sci_io.obj" "sensors.obj" "timer.obj" "wdog.obj" 
	-$(RM) "adc.d" "cap.d" "clk.d" "cpu.d" "f2802x_comp.d" "f2802x_cputimers.d" "f2802x_defaultisr.d" "f2802x_ecap.d" "f2802x_gpio.d" "f2802x_piectrl.d" "f2802x_pievect.d" "f2802x_sci.d" "f2802x_sysctrl.d" "flash.d" "gpio.d" "main.d" "mppt.d" "pie.d" "pll.d" "pwm.d" "sci.d" "sci_io.d" "sensors.d" "timer.d" "wdog.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

