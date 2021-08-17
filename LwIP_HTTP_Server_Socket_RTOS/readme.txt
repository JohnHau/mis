/**
  @page LwIP_HTTP_Server_Socket_RTOS LwIP HTTP Server Socket application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    LwIP/LwIP_HTTP_Server_Socket_RTOS/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LwIP http Server Socket application.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                               www.st.com/SLA0044
  *
  ******************************************************************************
   @endverbatim

@par Application Description 

This application guides STM32Cube HAL API users to run a http server application 
based on Socket API of LwIP TCP/IP stack
The communication is done with a web browser application in a remote PC.

this HTTP server contains two html pages:
  + the first page (home page) is static, it gives information about STM32F4
    and LwIP stack.
  + the second page is dynamically refreshed (every 1 s), it shows the RTOS 
    statistics in runtime

If the LCD is used (#define USE_LCD in main.h), log messages will be displayed 
to inform user about ethernet cable status and the IP address value, else this 
will be ensured by LEDs:
  + LED1: ethernet cable is connected.
  + LED1: ethernet cable is not connected.

If a DHCP server is available, a dynamic IP address can be allocated by enabling 
the DHCP process (#define USE_DHCP in main.h) 

Note: In this application the Ethernet Link ISR need the HAL time base to configure 
the Ethernet MAC, so the Ethernet Link interrupt priority must be set lower (numerically greater) 
than the HAL tick interrupt priority to ensure that the System tick increments while executing 
the Ethernet Link ISR.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in HAL time base ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the HAL time base interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the HAL time base is always set to 1 millisecond to have correct 
      HAL operation.
      
For more details about this application, refer to UM1713 "STM32Cube interfacing with LwIP and applications"

@par Keywords

Connectivity, LwIP, Ethernet, HTTP Server, Socket, TCP/IP, FreeRTOS, RTOS, DHCP	

@par Directory contents 

  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/app_ethernet.h                   header of app_ethernet.c file
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/ethernetif.h                     header for ethernetif.c file
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/lcd_log_conf.h                   LCD Log configuration file
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/stm32f4xx_hal_conf.h             HAL configuration file
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/stm32f4xx_it.h                   STM32 interrupt handlers header file
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/main.h                           Main program header file
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/lwipopts.h                       LwIP stack configuration options
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/FreeRTOSConfig.h                 FreeRTOS configuration options
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/httpserver-socket.h              header for httpserver-socket.c
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/stm32f4xx_it.c                   STM32 interrupt handlers
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/app_ethernet.c                   Ethernet specific module
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/main.c                           Main program
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/system_stm32f4xx.c               STM32F4xx system clock configuration file
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/ethernetif.c                     Interfacing LwIP to ETH driver
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/httpserver-socket.c              httpserver socket main thread
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/fsdata_custom.c                  ROM filesystem data (html pages)
  - LwIP/LwIP_HTTP_Server_Socket_RTOS/Src/stm32f4xx_hal_timebase_tim.c     HAL time base based on the hardware TIM
  

@par Hardware and Software environment

  - This application runs on STM32F407xx/STM32F417xx Devices.
    
  - This application has been tested with the following environments:
     - STM324xG-EVAL board
     - Http clients: Firefox Mozilla (v24) or Microsoft Internet Explorer (v8 and later)
     - DHCP server:  PC utility TFTPD32 (http://tftpd32.jounin.net/) is used as a DHCP server    
      
  - STM324xG-EVAL RevC Set-up
    - Connect the eval board to remote PC (through a crossover ethernet cable)
      or to your local network (through a straight ethernet cable)
  
  - Remote PC Set-up
    - Configure a static IP address for your remote PC 
      for example 192.168.0.11 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
