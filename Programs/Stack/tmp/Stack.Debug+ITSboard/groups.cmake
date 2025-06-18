# groups.cmake

# group Drivers/BSP/STM32F4xx_Nucleo_144
add_library(Group_Drivers_BSP_STM32F4xx_Nucleo_144 OBJECT
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/BSP/STM32F4xx_Nucleo_144/stm32f4xx_nucleo_144.c"
)
target_include_directories(Group_Drivers_BSP_STM32F4xx_Nucleo_144 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Drivers_BSP_STM32F4xx_Nucleo_144 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Drivers_BSP_STM32F4xx_Nucleo_144 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Drivers_BSP_STM32F4xx_Nucleo_144 PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Drivers/Board
add_library(Group_Drivers_Board OBJECT
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/startup/startup_stm32f429xx.s"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/startup/system_stm32f4xx.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/startup/stm32f4xx_it.c"
)
target_include_directories(Group_Drivers_Board PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Drivers_Board PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Drivers_Board PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Drivers_Board PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  __MICROLIB
  STM32F429xx
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/startup/startup_stm32f429xx.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)

# group Drivers/STM32F4xx_HAL_Driver
add_library(Group_Drivers_STM32F4xx_HAL_Driver OBJECT
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c"
)
target_include_directories(Group_Drivers_STM32F4xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Drivers_STM32F4xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Drivers_STM32F4xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Drivers_STM32F4xx_HAL_Driver PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Utils
add_library(Group_Utils OBJECT
  "${SOLUTION_ROOT}/../../stm32cubef4/Utilities/Fonts/font8.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Utilities/Fonts/font12.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Utilities/Fonts/font16.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Utilities/Fonts/font20.c"
  "${SOLUTION_ROOT}/../../stm32cubef4/Utilities/Fonts/font24.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/Consolas40.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/Consolas60.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/Consolas80.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/Consolas90.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/ConsolasBold40.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/ConsolasBold60.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/ConsolasBold80.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/ConsolasBold90.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/CourierNew48.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/CourierNewBold40.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/CourierNewBold60.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMono40.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMono60.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMono80.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMono90.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMonoMedium40.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMonoMedium60.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMonoMedium80.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/FiraMonoMedium90.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Utilities/AddFonts/fontsFLASH.c"
)
target_include_directories(Group_Utils PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Utils PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Utils PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Utils PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group LCD
add_library(Group_LCD OBJECT
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_Driver.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_GUI.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_Touch.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_SPI.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_GPIO.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_TIM.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_Tools.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/testsoftware.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_Debug.c"
  "${SOLUTION_ROOT}/../../DisplayWaveshare/Src/LCD_Demos.c"
)
target_include_directories(Group_LCD PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_LCD PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_LCD PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_LCD PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group ITS_BRD_LIB
add_library(Group_ITS_BRD_LIB OBJECT
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/error.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/lcd.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/init.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/terminal.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/keypad.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/delay.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/timer.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/USART_STM32F4xx.c"
  "${SOLUTION_ROOT}/../../ITS_BRD_LIB/Src/stdinout_USART.c"
)
target_include_directories(Group_ITS_BRD_LIB PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_ITS_BRD_LIB PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_ITS_BRD_LIB PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_ITS_BRD_LIB PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Program/User/Inc
add_library(Group_Program_User_Inc INTERFACE)
target_include_directories(Group_Program_User_Inc INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${SOLUTION_ROOT}/../../ITS_BRD_LIB/Inc
  ${SOLUTION_ROOT}/Inc
)
target_compile_definitions(Group_Program_User_Inc INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)

# group lwIP/Source
add_library(Group_lwIP_Source OBJECT
  "${SOLUTION_ROOT}/../../lwip/src/netif/ethernet.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ipv4/ip4.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ip.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ipv4/ip4_addr.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ipv4/ip4_frag.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ipv4/acd.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ipv4/dhcp.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ipv4/etharp.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/ipv4/icmp.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/def.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/mem.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/memp.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/netif.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/pbuf.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/tcp.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/tcp_in.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/tcp_out.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/timeouts.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/udp.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/inet_chksum.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/init.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/stats.c"
  "${SOLUTION_ROOT}/../../lwip/src/core/dns.c"
)
target_include_directories(Group_lwIP_Source PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_lwIP_Source PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_lwIP_Source PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_lwIP_Source PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Program/Arch/Inc
add_library(Group_Program_Arch_Inc INTERFACE)
target_include_directories(Group_Program_Arch_Inc INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  ${SOLUTION_ROOT}/Inc/arch
)
target_compile_definitions(Group_Program_Arch_Inc INTERFACE
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)

# group Program/User/Src
add_library(Group_Program_User_Src OBJECT
  "${SOLUTION_ROOT}/Src/main.c"
  "${SOLUTION_ROOT}/Src/led.c"
  "${SOLUTION_ROOT}/Src/lwip_interface.c"
  "${SOLUTION_ROOT}/Src/arch/sys_arch.c"
  "${SOLUTION_ROOT}/Src/tcp_server.c"
  "${SOLUTION_ROOT}/Src/udp_client.c"
  "${SOLUTION_ROOT}/Src/output.c"
  "${SOLUTION_ROOT}/Src/input.c"
  "${SOLUTION_ROOT}/Src/message.c"
)
target_include_directories(Group_Program_User_Src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Program_User_Src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Program_User_Src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Program_User_Src PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Program/Net/Src
add_library(Group_Program_Net_Src OBJECT
  "${SOLUTION_ROOT}/Src/net/ethernetif.c"
)
target_include_directories(Group_Program_Net_Src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Program_Net_Src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Program_Net_Src PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Program_Net_Src PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
