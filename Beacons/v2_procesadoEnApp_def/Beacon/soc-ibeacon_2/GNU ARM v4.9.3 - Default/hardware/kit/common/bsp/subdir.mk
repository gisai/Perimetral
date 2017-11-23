################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/kit/common/bsp/bsp_stk.c 

OBJS += \
./hardware/kit/common/bsp/bsp_stk.o 

C_DEPS += \
./hardware/kit/common/bsp/bsp_stk.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/kit/common/bsp/bsp_stk.o: ../hardware/kit/common/bsp/bsp_stk.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM48=1' -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emlib\inc" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\hardware\kit\common\halconfig" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\radio\rail_lib\common" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emlib\src" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\CMSIS\Include" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\hardware\kit\EFR32BG1_BRD4300C\config" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\hardware\kit\common\bsp" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\halconfig\inc\hal-config" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emdrv\sleep\inc" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\hardware\kit\common\drivers" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emdrv\uartdrv\inc" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\app\bluetooth_2.6\common\stack_bridge" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emdrv\common\inc" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\radio\rail_lib\chip\efr32" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emdrv\dmadrv\src" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\emdrv\dmadrv\inc" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\bootloader\api" -I"C:\Users\Borja\SimplicityStudio\v4_workspace\soc-ibeacon_2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/bsp/bsp_stk.d" -MT"hardware/kit/common/bsp/bsp_stk.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


