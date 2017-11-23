################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth_2.6/lib/EFR32BG1B/EABI/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/dmadrv/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32BG1B/Source/GCC/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: soc-ibeacon_2.axf

# Tool invocations
soc-ibeacon_2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\efr32bg1b232f256gm48.ld" -Xlinker -no-enum-size-warning -Xlinker -no-wchar-size-warning -Xlinker --gc-sections -Xlinker -Map="soc-ibeacon_2.map" -mfpu=fpv4-sp-d16 -mfloat-abi=hard -o soc-ibeacon_2.axf "./application_properties.o" "./gatt_db.o" "./init_app.o" "./init_board.o" "./init_mcu.o" "./main.o" "./pti.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/drivers/mx25flash_spi.o" "./platform/Device/SiliconLabs/EFR32BG1B/Source/GCC/startup_efr32bg1b.o" "./platform/emdrv/dmadrv/src/dmadrv.o" "./platform/emlib/src/em_adc.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_ldma.o" "./platform/emlib/src/em_leuart.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_usart.o" "C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\protocol\bluetooth_2.6\lib\EFR32BG1B\EABI\stack.a" "C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\protocol\bluetooth_2.6\lib\EFR32BG1B\EABI\binstack.o" "C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\protocol\bluetooth_2.6\lib\EFR32BG1B\EABI\binbootloader.o" "C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\protocol\bluetooth_2.6\lib\EFR32BG1B\GCC\bgapi.a" -lm -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: soc-ibeacon_2.hex'
	arm-none-eabi-objcopy -O ihex "soc-ibeacon_2.axf" "soc-ibeacon_2.hex"
	@echo ' '

	@echo 'Building bin file: soc-ibeacon_2.bin'
	arm-none-eabi-objcopy -O binary "soc-ibeacon_2.axf" "soc-ibeacon_2.bin"
	@echo ' '

	@echo 'Building s37 file: soc-ibeacon_2.s37'
	arm-none-eabi-objcopy -O srec "soc-ibeacon_2.axf" "soc-ibeacon_2.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "soc-ibeacon_2.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) soc-ibeacon_2.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
