################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/7_segment/Segment.c \
../HAL/7_segment/Segment_cfg.c 

OBJS += \
./HAL/7_segment/Segment.o \
./HAL/7_segment/Segment_cfg.o 

C_DEPS += \
./HAL/7_segment/Segment.d \
./HAL/7_segment/Segment_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/7_segment/%.o HAL/7_segment/%.su HAL/7_segment/%.cyclo: ../HAL/7_segment/%.c HAL/7_segment/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"F:/ARM_projects/traffic_lights_RTOS/traffic_RTOS/HAL/servo_motor" -I"F:/ARM_projects/traffic_lights_RTOS/traffic_RTOS/HAL/LCD" -I"F:/ARM_projects/traffic_lights_RTOS/traffic_RTOS/HAL/Common" -I"F:/ARM_projects/traffic_lights_RTOS/traffic_RTOS/HAL/7_segment" -IF:/ARM_projects/creative/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IF:/ARM_projects/creative/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IF:/ARM_projects/creative/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/include -IF:/ARM_projects/creative/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -IF:/ARM_projects/creative/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IF:/ARM_projects/creative/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IF:/ARM_projects/creative/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-7_segment

clean-HAL-2f-7_segment:
	-$(RM) ./HAL/7_segment/Segment.cyclo ./HAL/7_segment/Segment.d ./HAL/7_segment/Segment.o ./HAL/7_segment/Segment.su ./HAL/7_segment/Segment_cfg.cyclo ./HAL/7_segment/Segment_cfg.d ./HAL/7_segment/Segment_cfg.o ./HAL/7_segment/Segment_cfg.su

.PHONY: clean-HAL-2f-7_segment

