################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Session19.elf

dependents:
	-cd C:/Users/jared/workspace/nucleo-l152re_hal_lib/Debug && $(MAKE) all

# Tool invocations
Session19.elf: $(OBJS) $(USER_OBJS) C:/Users/jared/workspace/nucleo-l152re_hal_lib/Debug/libnucleo-l152re_hal_lib.a C:\Users\jared\workspace\Session19/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -L"C:\Users\jared\workspace\nucleo-l152re_hal_lib\Debug" -T"C:/Users/jared/workspace/Session19/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "Session19.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "Session19.elf" "Session19.bin"
	arm-none-eabi-size "Session19.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/jared/workspace/nucleo-l152re_hal_lib/Debug/libnucleo-l152re_hal_lib.a:

-include ../makefile.targets
