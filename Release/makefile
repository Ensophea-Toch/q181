################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := c:\tools\build\make381\rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Q161
BUILD_ARTIFACT_EXTENSION := img
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
RAW_BINARY += \
Q161.elf \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Q161.img

# Tool invocations
Q161.img: $(RAW_BINARY) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Q161 Binary Packer'
	c:\tools\NOV30\vpostype\Q161\dtools  mkappimg $(RAW_BINARY) "Q161.img"
	@echo 'Finished building target: $@'
	@echo ' '

Q161.elf: $(OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Q161 Linker'
	c:\gcc-arm-none-eabi\bin\arm-none-eabi-ld -o "Q161.elf" $(OBJS) "c:\tools\NOV30\vpostype\Q161\inits\core_stub.o" "C:\tools\NOV30\vpostype\Q161\lib\lib_commonUniversal.a" "c:\tools\NOV30\vpostype\Q161\lib\libapicore.a" "C:\tools\NOV30\vpostype\Q161\lib\Q390&Q161_Hw1.0_L610_LIB_95c27660_V1.01.06_20230421_Release.a" "c:\tools\NOV30\vpostype\Q161\lib\libQREncode.a" "c:\tools\NOV30\vpostype\Q161\lib\libimageCore.a" "c:\tools\NOV30\vpostype\Q161\lib\libmbedtls.a" "c:\tools\NOV30\vpostype\Q161\lib\libmqttClient.a" "c:\gcc-arm-none-eabi\libc\libc.a" "c:\gcc-arm-none-eabi\libc\libm.a" "c:\gcc-arm-none-eabi\lib\gcc\arm-none-eabi\7.2.1\thumb\v7-ar\fpv3\hard\libgcc.a" -Map Q161.map -nostdlib --gc-sections -T c:\tools\NOV30\vpostype\Q161\inits\app_flashimg.ld
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Q161.elf Q161.img
	-@echo ' '

post-build:
	-c:\tools\NOV30\vpostype\Q161\pack Q161 c:\tools & copy c:\tools\NOV30\vpostype\Q161\prk_json.txt .\prk_json.txt & c:\tools/NOV30/vpostype/Q161/VanstoneSign Q161.img & del prk_json.txt
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
