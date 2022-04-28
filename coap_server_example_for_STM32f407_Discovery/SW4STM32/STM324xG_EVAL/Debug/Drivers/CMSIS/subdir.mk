################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Src/system_stm32f4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f4xx.o: C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Src/system_stm32f4xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_STM324xG_EVAL -c -I../../../Inc -I../../../Middlewares/Third_Party/libcoap/examples/application -I../../../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../../../Middlewares/Third_Party/libcoap/include/coap2 -I../../../Middlewares/Third_Party/libcoap/port/include -I../../../Middlewares/Third_Party/libcoap/port/include/coap -I../../../Src -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/CMSIS/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM324xG_EVAL -I../../../Drivers/BSP/Components -I../../../Middlewares/Third_Party/LwIP/src/include -I../../../Middlewares/Third_Party/LwIP/system -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Utilities -I../../../Utilities/Log -I"C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Middlewares/Third_Party/LwIP/src/apps" -I"C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Middlewares/Third_Party/libcoap/ext/tinydtls" -I"C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Middlewares/Third_Party/libcoap/ext/tinydtls/aes" -I"C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Middlewares/Third_Party/libcoap/ext/tinydtls/ecc" -I"C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Middlewares/Third_Party/libcoap/ext/tinydtls/sha2/testvectors" -I"C:/coap/COAP_server_for_STM32f407_Discovery/coap_server_example_for_STM32f407_Discovery/Middlewares/Third_Party/libcoap/ext/tinydtls/tests" -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

